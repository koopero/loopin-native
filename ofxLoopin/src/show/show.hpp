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
    DIVIDE
  };

  ofxLoopinControlEnum<Alpha,IGNORE> alpha;

  void draw();

  string getBufferDescription() {
    return _bufferDescription;
  };

protected:
  void addSubControls();
  static ofxLoopinShader alphaDivideShader;

private:
  string _bufferDescription;
};
// end namespace
};
