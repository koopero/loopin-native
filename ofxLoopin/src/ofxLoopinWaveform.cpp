#include "ofxLoopinWaveform.h"

void ofxLoopinWaveform::renderBuffer( ofxLoopinBuffer * buffer ) {
  // Ensure the soundstream is running
  if ( !streamIsOpen ) {
    soundStream.printDeviceList();
    soundStream.setInput( *this );
    streamIsOpen = soundStream.setup( 0, 1, 44100, 256, 1 );
  }

  if ( !buffer )
    buffer = getBuffer( true );

  buffer->defaultSize( getBounds() );

  if ( !buffer->begin() ) {
    // TODO: Error here
    return;
  }




  ofImage output;
  output.allocate( 64, 4, OF_IMAGE_COLOR );
  output.setColor( ofColor(0,0,255,255));

  ofPixels &pixels = output.getPixels();

  for ( int i = 0; i < samples.size(); i ++ ) {
    float sample = samples.getSample( i, 0 );

    if ( i < 64*3 )
      pixels[i] = sample*255.0;
  }

  output.update();
  output.draw(0,0);
  buffer->end();
  samples.clear();
}

ofRectangle ofxLoopinWaveform::getBounds() {
  return ofRectangle( 0, 0, 1, 64 );
}

void ofxLoopinWaveform::audioIn(ofSoundBuffer &buffer) {
  samples.append( buffer );
}
