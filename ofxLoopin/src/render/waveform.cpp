#include "waveform.hpp"

ofxLoopinShader ofxLoopin::render::waveform_imp::shader = ofxLoopinShader(
// name
"solidRGBA",
// frag
#ifndef TARGET_OPENGLES
"#version 150 \n\
uniform float red; \n\
uniform float green; \n\
uniform float blue; \n\
uniform float alpha; \n\
out vec4 OUT; \n\
void main() \n\
{ \n\
  OUT = vec4( red, green, blue, alpha ); \n\
} \n\
"
#else
"uniform float red; \n\
uniform float green; \n\
uniform float blue; \n\
uniform float alpha; \n\
void main() \n\
{ \n\
  gl_FragColor = vec4( red, green, blue, alpha ); \n\
} \n\
"
#endif
) ;

Json::Value ofxLoopin::render::waveform::infoGet() {
  Json::Value result;

  ofSoundStream stream;
  std::vector<ofSoundDevice> devices = stream.getDeviceList();
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

void ofxLoopin::render::waveform_imp::renderBuffer( ofxLoopinBuffer * buffer ) {
  // Ensure the soundstream is running
  int channels = (int) ofxLoopin::render::waveform_imp::channels;

  if ( channels < 1 )
    return;

  int deviceID = ofxLoopin::render::waveform_imp::deviceID;

  if ( soundStream.getNumInputChannels() != channels || deviceID != _deviceID ) {
    soundStream.setDeviceID( deviceID );
    streamIsOpen = soundStream.setup( 0, channels, 48000, 256, 8 );
    if ( streamIsOpen ) {
      soundStream.setInput( *this );
      _deviceID = deviceID;

      ofxLoopinEvent event = ofxLoopinEvent("open");
      event.data["deviceID"] = (int) deviceID;
      dispatch( event );
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

  float _duration = ofxLoopin::render::waveform_imp::duration;
  float _samplesDuration = (float) samples.getDurationMicros() / 1000000.0;
  int size = _duration ? floor( bufferWidth * _samplesDuration / _duration ) : bufferWidth;

  if ( !size )
    return;

  renderScrollExisting( buffer, size );

  int k = samples.getNumFrames();

  buffer->begin();
  ofSetupScreen();
  shader.begin();

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
      drawSample( x, channel, sample * sampleSign );
    }
  }

  shader.end();
  buffer->end();
  samples.clear();
}

void ofxLoopin::render::waveform_imp::renderScrollExisting( ofxLoopinBuffer * buffer, int offset ) {
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

  int y = ofxLoopin::render::waveform_imp::y;
  int channels = ofxLoopin::render::waveform_imp::channels;

  // Make sure everything else in the buffer is preserved.
  if ( y > 0 || y + channels < bufferHeight ) {
    texture->draw( 0, 0 );
  }

  texture->drawSubsection( offset, y, bufferWidth, channels, 0, y, bufferWidth, channels );
  buffer->end();
}

void ofxLoopin::render::waveform_imp::drawSample( int x, int y, float sample ) {
  shader.applyUniformFloat( "red", sample );
  shader.applyUniformFloat( "green", sample );
  shader.applyUniformFloat( "blue", sample );
  shader.applyUniformFloat( "alpha", 1 );

  ofDrawRectangle( x,y+ofxLoopin::render::waveform_imp::y,1,1);
}

void ofxLoopin::render::waveform_imp::computeSample( float & sample, int & sign ) {
  sign = sample == 0 ? 0 : fabs( sample ) / sample;
  sample = fabs( sample );

  float squelch = ofxLoopin::render::waveform_imp::squelch;
  sample = sample < squelch ? 0 : sample - squelch;

  sample *= ofxLoopin::render::waveform_imp::gain;

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

ofRectangle ofxLoopin::render::waveform_imp::getBounds() {
  return ofRectangle( 0, 0, 256, (int) y + (int) channels );
}

void ofxLoopin::render::waveform_imp::audioIn(ofSoundBuffer &buffer) {
  std::lock_guard<std::mutex> guard(samples_mutex);

  samples.setNumChannels( buffer.getNumChannels() );

  if ( samples.size() < 1000000 ) {
    samples.append( buffer );
  }
}
