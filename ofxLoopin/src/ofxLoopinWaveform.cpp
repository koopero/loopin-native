#include "ofxLoopinWaveform.h"

void ofxLoopinWaveform::renderBuffer( ofxLoopinBuffer * buffer ) {
  // Ensure the soundstream is running
  int channels = (int) ofxLoopinWaveform::channels;

  if ( channels < 1 )
    return;

  if ( !streamIsOpen ) {
    soundStream.setInput( *this );
    streamIsOpen = true;
  }

  int deviceID = ofxLoopinWaveform::deviceID;

  if ( soundStream.getNumInputChannels() != channels || deviceID != _deviceID ) {
    streamIsOpen = soundStream.setup( 0, channels, 44100, 256, 1 );
    soundStream.setDeviceID( deviceID );
    _deviceID = deviceID;
  }

  if ( !buffer )
    buffer = getBuffer( true );

  buffer->defaultSize( getBounds() );

  if ( !samples.size() )
    return;

  int bufferWidth = buffer->getWidth();
  int bufferHeight = buffer->getHeight();

  float _duration = ofxLoopinWaveform::duration;
  float _samplesDuration = (float) samples.getDurationMicros() / 1000000.0;
  int size = floor( bufferWidth * _samplesDuration / _duration );

  if ( !size )
    return;

  if ( size < bufferWidth ) {
    buffer->flip();
    buffer->begin();
    buffer->draw( bufferWidth, bufferHeight, size );
  } else {
    buffer->begin();
  }

  ofFloatImage output;
  output.allocate( size, channels, OF_IMAGE_COLOR );
  output.setColor( ofColor(0,0,0,255) );

  ofFloatPixels & pixels = output.getPixels();

  int k = samples.getNumFrames();

  if ( k > size ) {
    for ( int i = 0; i < k; i ++ ) {
      int x = floor( ( (float) i / (float) (k-1) ) * size );
      if ( x >= size )
        break;

      for ( int channel = 0; channel < channels; channel++ ) {
        ofFloatColor pixel = pixels.getColor( x, channel );
        float sample = samples.getSample( i, channel );
        float sampleSign;

        computeSample( sample, sampleSign );

        float last = pixel[0];
        float lastAbs = fabs( last );
        float lastSign = last == 0 ? 1 : last / lastAbs;

        sample = max( lastAbs, sample );

        pixel.setHsb( 0,0,sample);
        pixels.setColor( x, channel, pixel );
      }
    }
  } else {
    for ( int x = 0; x < size && x < bufferWidth; x ++ ) {

      float i = ( (float) x / (float) size ) * k;
      for ( int channel = 0; channel < channels; channel++ ) {
        ofFloatColor pixel;
        pixel.a = 1.0;
        float sample = samples.getSample( i, channel );
        float sampleSign;

        computeSample( sample, sampleSign );

        pixel.setHsb( 0,0,sample);
        pixels.setColor( x, channel, pixel );
      }
    }
  }

  // cerr << "done " << x << " < " << size << endl;


  output.update();
  output.draw(0,0,size,max(channels,bufferHeight));
  output.clear();

  buffer->end();
  samples.clear();
}

void ofxLoopinWaveform::computeSample( float & sample, float & sign ) {
  sign = sample == 0 ? 1 : fabs( sample ) / sample;
  sample = fabs( sample );

  float squelch = ofxLoopinWaveform::squelch;
  sample = sample < squelch ? 0 : sample - squelch;

  sample *= ofxLoopinWaveform::gain;

  switch ( phase.getEnumValue() ) {
    case PHASE_ABS:
      sign = 1; // abs == true
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
}

ofRectangle ofxLoopinWaveform::getBounds() {
  return ofRectangle( 0, 0, 1200, 1 );
}

void ofxLoopinWaveform::audioIn(ofSoundBuffer &buffer) {
  samples.setNumChannels( buffer.getNumChannels() );
  samples.append( buffer );
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
