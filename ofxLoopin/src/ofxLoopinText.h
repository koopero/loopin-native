#pragma once

#include "ofxLoopinRender.h"

#include "ofGraphics.h"
/** loopin/type/text/sub:
  text:
    type: string
*/
class ofxLoopinText : public ofxLoopinRender {
public:
  string text = "hello, world";

  void draw( const ofRectangle & area );
  ofRectangle getBounds();

  virtual void renderBuffer( ofxLoopinBuffer * buffer );

protected:
  void addSubControls() {
    addSubControl( "text", new ofxLoopinControlValue( &text ) );
  }

  void patchString( string value ) {
    text = value;
  };
};
