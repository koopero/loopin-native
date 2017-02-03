#pragma once

#include "ofImage.h"
#include "ofTexture.h"

#include "ofxLoopinControl.h"
// #include "ofxLoopinLoader.h"
#include "ofxLoopinRender.h"
#include "ofxLoopinMap.h"

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
  string src;
  bool reload;


  void render( ofxLoopinBuffer * buffer );

  void load( string filePath );

  bool opt_resize = true;
protected:
  void updateLocal();

  void patchString( const string & value ) {
    src = value;
  }

  void addSubControls() {
    addSubControl("src", new ofxLoopinControlValue( &src ) );
  };

private:
  ofTexture texture;

  string _loaded;

};
