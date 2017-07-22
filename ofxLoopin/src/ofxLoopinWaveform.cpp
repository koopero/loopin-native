#include "ofxLoopinWaveform.h"

void ofxLoopinWaveform::renderBuffer( ofxLoopinBuffer * buffer ) {
  // Ensure the soundstream is running
  int channels = (int) ofxLoopinWaveform::channels;

  if ( channels < 1 )
    return;

  int deviceID = ofxLoopinWaveform::deviceID;

  if ( soundStream.getNumInputChannels() != channels || deviceID != _deviceID ) {
    soundStream.setDeviceID( deviceID );
    streamIsOpen = soundStream.setup( 0, channels, 48000, 256, 8 );
    if ( streamIsOpen ) {
      soundStream.setInput( *this );
      _deviceID = deviceID;
    }
  }

  if ( !buffer )
    buffer = getBuffer( true );

  buffer->defaultSize( getBounds() );

  std::lock_guard<std::mutex> guard(samples_mutex);

  if ( !samples.size() )
    return;

  int bufferWidth = buffer->getWidth();
  int bufferHeight = buffer->getHeight();

  float _duration = ofxLoopinWaveform::duration;
  float _samplesDuration = (float) samples.getDurationMicros() / 1000000.0;
  int size = _duration ? floor( bufferWidth * _samplesDuration / _duration ) : bufferWidth;

  if ( !size )
    return;

  renderScrollExisting( buffer, size );



  ofxLoopinShader * shader = ofxLoopinWaveform::shader.getPointer( true );
  if ( !shader ) { dispatch("shaderFault"); return; }

  int k = samples.getNumFrames();

  buffer->begin();
  ofSetupScreen();
  shader->begin();

  for ( int channel = 0; channel < channels; channel++ ) {
    for ( int x = 0; x < size && x < bufferWidth; x ++ ) {

      int sampleStart = floor( (float) x / (float) size * k );
      int sampleEnd = ceil( (float) x / (float) size * k );

      float sample = 0.0;
      int sampleSign = 0;
      for ( int i = sampleStart; ( i == sampleStart || i < sampleEnd ) && i < samples.getNumFrames(); i ++ ) {
        int ssSign = 0;
        float ssValue = samples.getSample( i, channel );
        computeSample( ssValue, ssSign );

        if ( !sampleSign )
          sampleSign = ssSign;

        sample = max( sample, ssValue );
      }
      drawSample( shader, x, channel, sample * sampleSign );
    }
  }

  shader->end();
  buffer->end();
  samples.clear();
}

void ofxLoopinWaveform::renderScrollExisting( ofxLoopinBuffer * buffer, int offset ) {
  int bufferWidth = buffer->getWidth();
  int bufferHeight = buffer->getHeight();


  if ( offset >= bufferWidth )
    return;

  ofTexture * texture = buffer->getTexture();

  if ( !texture || !texture->isAllocated() )
    return;

  buffer->flip();
  buffer->begin();

  ofSetupScreen();
  glDisable( GL_CULL_FACE );
  ofDisableBlendMode();
  ofDisableDepthTest();

  int y = ofxLoopinWaveform::y;
  int channels = ofxLoopinWaveform::channels;

  // Make sure everything else in the buffer is preserved.
  if ( y > 0 || y + channels < bufferHeight ) {
    texture->draw( 0, 0 );
  }

  texture->drawSubsection( offset, y, bufferWidth, channels, 0, y, bufferWidth, channels );
  buffer->end();
}

void ofxLoopinWaveform::drawSample( ofxLoopinShader * shader, int x, int y, float sample ) {
  shader->shader.setUniform1f( "red", sample );
  shader->shader.setUniform1f( "green", sample );
  shader->shader.setUniform1f( "blue", sample );
  shader->shader.setUniform1f( "alpha", 1 );
  // sample = sample > 1 ? 1 : sample < 0 ? 0 : sample;
  // sample *= 255.0;
  // ofSetColor( sample, sample, sample );

  ofDrawRectangle( x,y+ofxLoopinWaveform::y,1,1);
}

void ofxLoopinWaveform::computeSample( float & sample, int & sign ) {
  sign = sample == 0 ? 0 : fabs( sample ) / sample;
  sample = fabs( sample );

  float squelch = ofxLoopinWaveform::squelch;
  sample = sample < squelch ? 0 : sample - squelch;

  sample *= ofxLoopinWaveform::gain;

  switch ( phase.getEnumValue() ) {
    case PHASE_ABS:
      sign = 1;
    break;

    case PHASE_POS:
      if ( sign < 0 )
        sample = 0;
    break;

    case PHASE_NEG:
      if ( sign > 0 )
        sample = 0;
      else
        sign = 1;
    break;

    case PHASE_BOTH:

    break;
  }

  if ( sample == 0 )
    sign = 0;
}

ofRectangle ofxLoopinWaveform::getBounds() {
  return ofRectangle( 0, 0, 256, (int) y + (int) channels );
}

void ofxLoopinWaveform::audioIn(ofSoundBuffer &buffer) {
  std::lock_guard<std::mutex> guard(samples_mutex);

  samples.setNumChannels( buffer.getNumChannels() );

  if ( samples.size() < 1000000 ) {
    samples.append( buffer );
  }
}

Json::Value ofxLoopinWaveform::getInfo() {
  Json::Value result;

  ofSoundStream stream;
  vector<ofSoundDevice> devices = stream.getDeviceList();
  int ji = 0;
  for ( int i = 0; i < devices.size(); i ++ ) {
    if ( !devices[i].inputChannels )
      continue;
    result["devices"][ji]["deviceID"] = devices[i].deviceID;
    result["devices"][ji]["inputChannels"] = devices[i].inputChannels;
    result["devices"][ji]["name"] = devices[i].name;
    ji++;
  }

  return result;
}
