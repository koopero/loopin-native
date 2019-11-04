#include "ofxLoopinFft.h"


void ofxLoopinFft::renderBuffer( ofxLoopinBuffer * buffer ) {
  // Ensure the soundstream is running
  if ( !fftLive ) {
    fftLive = new ofxEasyFft();
    fftLive->setup( 1024 );
    fftLive->setUseNormalization( false );
  }

  fftLive->update();


  if ( !buffer )
    buffer = getBuffer( true );

  buffer->defaultSize( getBounds() );

  int bufferWidth = buffer->getWidth();
  int bufferHeight = buffer->getHeight();

  if ( bufferWidth > 1 ) {
    buffer->flip();
    buffer->begin();
    buffer->draw( bufferWidth, bufferHeight, 1 );
  } else {
    buffer->begin();
  }


  ofImage output;
  output.allocate( 1, bufferHeight, OF_IMAGE_COLOR );
  output.setColor( ofColor(0,0,255,255) );

  ofPixels &pixels = output.getPixels();

  for ( int y = 0; y < bufferHeight; y++ ) {
    float a = (float) y / (float) bufferHeight;
    float freq = 0.0 + a * 500.0;
    float s = fftLive->fft->getAmplitudeAtFrequency( freq );
    s = ofMap(
      s,
      0.01,
      0.3,
      0, 1,
      true
    );

    s = pow(s,0.5);

    unsigned char c = ofMap( s, 0, 1, 0, 255, true );
    pixels.setColor( 0, y, ofColor( c,c,c,255) );
  }


  output.update();
  output.draw(0,0);
  output.clear();

  buffer->end();
}

ofRectangle ofxLoopinFft::getBounds() {
  return ofRectangle( 0, 0, 128, 64 );
}
