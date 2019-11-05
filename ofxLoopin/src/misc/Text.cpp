#include "./Text.hpp"

ofRectangle ofxLoopin::misc::Text::getBounds() {
  return ofRectangle( 0, 0, 8 * text.size(), 12 );
}

void ofxLoopin::misc::Text::draw( const ofRectangle & area ) {
  ofDrawBitmapString( text, 0, 10 );
}


void ofxLoopin::misc::Text::renderBuffer( ofxLoopin::base::Buffer * buffer ) {
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