#include "ofxLoopinFFT.h"


void ofxLoopinFFT::renderBuffer( ofxLoopinBuffer * buffer ) {
  // Ensure the soundstream is running
  // if ( !fftIsOpen) {
  //   fftLive.setup();
  //   fftIsOpen = true;
  // }

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

  output.update();
  output.draw(0,0);
  output.clear();
  
  buffer->end();
}

ofRectangle ofxLoopinFFT::getBounds() {
  return ofRectangle( 0, 0, 1, 64 );
}
