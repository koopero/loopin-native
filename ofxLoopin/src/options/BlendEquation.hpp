#pragma once
#include "../control/GLEnum.hpp"

namespace ofxLoopin { namespace options {
class BlendEquation : public ofxLoopin::control::GLEnum {
protected: void enumAddOptions() {
  EnumGLIntAddOption(GL_NONE);
  EnumGLIntAddOption(GL_FUNC_ADD);
  EnumGLIntAddOption(GL_ZERO);
  EnumGLIntAddOption(GL_FUNC_SUBTRACT);
  EnumGLIntAddOption(GL_FUNC_REVERSE_SUBTRACT);

  #ifndef TARGET_OPENGLES
  EnumGLIntAddOption(GL_MIN);
  EnumGLIntAddOption(GL_MAX);
  #endif
};
};
}}
