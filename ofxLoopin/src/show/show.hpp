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
    IGNORE,
    MULTIPLY,
    DIVIDE,
    SHOW
  };

  ofxLoopinControlEnum<Alpha,IGNORE> alpha;

  void draw();

  string getBufferDescription() {
    return _bufferDescription;
  };

protected:
  void addSubControls();
  static ofxLoopinShader alphaDivideShader;
  static ofxLoopinShader alphaShowShader;


private:
  string _bufferDescription;
};
// end namespace
};
