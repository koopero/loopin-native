#include "ofxLoopinWaveform.h"

void ofxLoopinWaveform::renderBuffer( ofxLoopinBuffer * buffer ) {
  // Ensure the soundstream is running
  if ( !streamIsOpen ) {
    soundStream.setInput( *this );
    streamIsOpen = soundStream.setup( 0, 1, 44100, 256, 1 );
  }

  if ( !buffer )
    buffer = getBuffer( true );

  buffer->defaultSize( getBounds() );

  if ( !samples.size() )
    return;

  int bufferWidth = buffer->getWidth();
  float _duration = ofxLoopinWaveform::duration;
  float _samplesDuration = (float) samples.getDurationMicros() / 1000000.0;
  int size = floor( bufferWidth * _samplesDuration / _duration );

  if ( !size )
    return;

  if ( size < bufferWidth ) {
    buffer->flip();
    buffer->begin();
    buffer->draw( bufferWidth, 1, size );
  } else {
    buffer->begin();
  }


  ofFloatImage output;
  output.allocate( size, 1, OF_IMAGE_COLOR );
  output.setColor( ofColor(0,0,0,255) );

  ofFloatPixels & pixels = output.getPixels();

  int k = samples.size();
  int channels = 1;

  if ( k > size ) {
    for ( int i = 0; i < k; i ++ ) {
      int x = floor( ( (float) i / (float) (k-1) ) * size );
      ofFloatColor pixel = pixels.getColor( x, 0 );
      int channel = 0;
      float sample;
      for ( ; channel < channels && channel < 4; channel++ ) {
        sample = samples.getSample( i, channel );
        float sampleSign;

        computeSample( sample, sampleSign );

        float last = pixel[0];
        float lastAbs = fabs( last );
        float lastSign = last == 0 ? 1 : last / lastAbs;

        sample = max( lastAbs, sample );
        pixel[channel] = sample * sampleSign;
      }

      for ( ; channel < 3; channel ++ )
        pixel[channel] = sample;

      pixels.setColor( x, 0, pixel );
    }
  } else {
    for ( int x = 0; x < size && x < bufferWidth; x ++ ) {
      ofFloatColor pixel;
      pixel.a = 1.0;

      float i = ( (float) x / (float) size ) * k;
      float sample = 1.0;
      int channel = 0;
      for ( ; channel < channels && channel < 4; channel++ ) {
        sample = samples.getSample( i, channel );
        float sampleSign;

        computeSample( sample, sampleSign );

        pixel[channel] = sample * sampleSign;
      }

      for ( ; channel < 3; channel ++ )
        pixel[channel] = sample;

      pixels.setColor( x, 0, pixel );
    }
  }

  // cerr << "done " << x << " < " << size << endl;


  output.update();
  output.draw(0,0);
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
  samples.append( buffer );
}
