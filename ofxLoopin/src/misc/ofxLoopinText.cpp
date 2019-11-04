#include "ofxLoopinText.h"

ofRectangle ofxLoopinText::getBounds() {
  return ofRectangle( 0, 0, 8 * text.size(), 12 );
}

void ofxLoopinText::draw( const ofRectangle & area ) {
  ofDrawBitmapString( text, 0, 10 );
}


void ofxLoopinText::renderBuffer( ofxLoopinBuffer * buffer ) {
  if ( !buffer )
    return;

  ofRectangle bounds = getBounds();
  buffer->setSize( bounds.getWidth(), bounds.getHeight() );

  if ( !buffer->begin() )
    return;

  shaderDefault.begin();

  if ( clear ) {
    ofClear( 0, 0, 0, 0 );
  }

  draw( bounds );
  shaderDefault.end();

  buffer->end();
}