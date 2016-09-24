#include "ofxLoopinText.h"

ofRectangle ofxLoopinText::getBounds() {
  return ofRectangle( 0, 0, 8 * text.size(), 12 );
}

void ofxLoopinText::draw( const ofRectangle & area ) {
  ofDrawBitmapString( text, 0, 10 );
}
