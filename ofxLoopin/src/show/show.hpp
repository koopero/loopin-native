#pragma once

#include "./control/Enum.hpp"
#include "ofxLoopinTexture.h"

/** loopin/type/show:
  type: texture
*/
namespace ofxLoopin {

  
class Show : public ofxLoopinTexture {
public:
  enum Alpha {
    IGNOREX,
    MULTIPLY,
    DIVIDE,
    SHOW
  };

  ofxLoopin::control::Enum<Alpha,IGNOREX> alpha;

  void draw();

  string getBufferDescription() {
    return _bufferDescription;
  };

protected:
  void addSubControls();
  static ofxLoopin::shader::Shader alphaDivideShader;
  static ofxLoopin::shader::Shader alphaShowShader;


private:
  string _bufferDescription;
};
// end namespace
};
