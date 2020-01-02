#pragma once
#include "../control/GLEnum.hpp"
/** loopin/type/textureFilter:
    type: options
    options:
      - linear
      - nearest
  */
  
namespace ofxLoopin { namespace options {
class Filter : public ofxLoopin::control::GLEnum {
protected: void enumAddOptions() {
  EnumGLIntAddOption(GL_NEAREST);
  EnumGLIntAddOption(GL_LINEAR);
};
};
}}
