#pragma once

#include "ofxLoopinControlEnum.h"
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

  ofxLoopinControlEnum<Alpha,IGNOREX> alpha;

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
