#pragma once

#include "ofImage.h"
#include "ofTexture.h"

#include "../control/Control.hpp"
#include "../control/Bool.hpp"
#include "../control/Value.hpp"

#include "ofxLoopinRender.h"
#include "ofxLoopinMap.h"
#include "../control/Box.hpp"

/** loopin/type/image:
  trigger: true
  sub:
    src:
      file:
        - image/jpeg
        - image/png
*/

class ofxLoopinImage : public ofxLoopinRender {
public:
  ofxLoopinImage() {
    _createBuffer = false;
  }
  string src;

  ofxLoopin::control::Box box;
  ofxLoopin::control::Box crop;
  ofxLoopin::control::Bool replace;

  void renderBuffer( ofxLoopinBuffer * buffer );
  void load( string filePath );

protected:
  void updateLocal();

  void patchString( string value ) {
    src = value;
  }

  void addSubControls() {
    addSubControl("buffer", &buffer );
    addSubControl("box", &box );
    addSubControl("crop", &crop );
    addSubControl("replace", &replace );

    addSubControl("src", new ofxLoopin::control::Value( &src ) );
  };

private:
  ofTexture texture;

  bool _dirty = true;
  string _loaded;

};
