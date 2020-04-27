#pragma once
#include "../control/GLEnum.hpp"
/** loopin/type/textureFilter:
    type: options
    options:
      - linear
      - nearest
  */
  
namespace ofxLoopin { namespace options {
class Filter : public control::Enum<GLenum,GL_NEAREST>  {
protected: void enumAddOptions() {
  enumAddOption("nearest", GL_NEAREST);
  EnumGLIntAddOption(GL_NEAREST);
  enumAddOption("linear", GL_LINEAR);
  EnumGLIntAddOption(GL_LINEAR);
};
};
}}
