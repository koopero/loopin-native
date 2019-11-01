#pragma once

#include "../ofxLoopinLoader.h"
#include "../ofxLoopinControlValue.h"

/** loopin/type/shaderElement
type: source
sourceType: glsl
*/

namespace ofxLoopin { namespace shader {
class ShaderElement : public ofxLoopinLoader {
public:
  string file;
  string data;

  void load();
  void loadDefault();

  bool dataIsNew = false;

  bool isDataReady() {
    return data.size() > 0;
  }

protected:
  string _loadedFile;

  void addSubControls() {
    addSubControl( "file", new ofxLoopinControlValue( &file ) );
    addSubControl( "data", new ofxLoopinControlValue( &data ) );
  };

  string findDefaultFile();

  void patchLocal( const ofJson & value ) {
    dataIsNew = true;
  }

  void patchString( string str ) {
    data = str;
    dataIsNew = true;
  };

  /* Heuristically determine whether a given string is
    a filename or GLSL source. */
  bool is_stringGLSL( const string & str );
};
}};