#pragma once

#include "../render/Render.hpp"

#include "ofGraphics.h"
/** loopin/type/text/sub:
  text:
    type: string
*/
namespace ofxLoopin { namespace misc {
class Text : public ofxLoopin::render::Render {
public:
  string text = "hello, world";

  void draw( const ofRectangle & area );
  ofRectangle getBounds();

  virtual void renderBuffer( ofxLoopin::base::Buffer * buffer );

protected:
  void addSubControls() {
    addSubControl( "text", new ofxLoopin::control::Value( &text ) );
  }

  void patchString( string value ) {
    text = value;
  };
};
}};