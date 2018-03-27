#pragma once

#include "ofImage.h"
#include "ofTexture.h"

#include "ofxLoopinControl.h"
#include "ofxLoopinControlBool.h"
// #include "ofxLoopinLoader.h"
#include "ofxLoopinRender.h"
#include "ofxLoopinMap.h"
#include "../type/Box.hpp"

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

  ofxLoopin::type::Box box;
  ofxLoopin::type::Box crop;
  ofxLoopinControlBool replace;

  void renderBuffer( ofxLoopinBuffer * buffer );
  void load( string filePath );

protected:
  void updateLocal();

  void patchString( const string & value ) {
    src = value;
  }

  void addSubControls() {
    addSubControl("buffer", &buffer );
    addSubControl("box", &box );
    addSubControl("crop", &crop );
    addSubControl("replace", &replace );

    addSubControl("src", new ofxLoopinControlValue( &src ) );
  };

private:
  ofTexture texture;

  bool _dirty = true;
  string _loaded;

};
