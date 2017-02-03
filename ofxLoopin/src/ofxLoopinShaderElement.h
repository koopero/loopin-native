#pragma once

#include "ofxLoopinLoader.h"
#include "ofxLoopinMap.h"
#include "ofxLoopinControlValue.h"

/** loopin/type/shaderElement
type: source
sourceType: glsl
*/

class ofxLoopinShaderElement : public ofxLoopinLoader {
public:
  string file;
  string data;

  void load();

  bool dataIsNew;

  bool isDataReady() {
    return data.size() > 0;
  }

protected:
  string _loadedFile;

  void addSubControls() {
    addSubControl( "src", new ofxLoopinControlValue( &file ) );
    addSubControl( "data", new ofxLoopinControlValue( &data ) );
  };

  void patchLocal( const Json::Value & value ) {
    // cerr << "shaderElement::patchLocal " << path << endl;

    dataIsNew = true;
  }

  void patchString( const string & str ) {
    if ( isStringGLSL( str ) ) {
      data = str;
      dataIsNew = true;
    } else {
      file = str;
      _loadedFile = "";
      dataIsNew = true;
    }
  };



  /* Heuristically determine whether a given string is
    a filename or GLSL source. */
  bool isStringGLSL( const string & str );


};
