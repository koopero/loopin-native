#pragma once
#include "../type/GLEnum.hpp"

namespace ofxLoopin { namespace options {
class BlendEquation : public type::GLEnum {
protected: void enumAddOptions() {
  EnumGLIntAddOption(GL_FUNC_ADD);
  EnumGLIntAddOption(GL_NONE);
  EnumGLIntAddOption(GL_ZERO);
  EnumGLIntAddOption(GL_FUNC_SUBTRACT);
  EnumGLIntAddOption(GL_FUNC_REVERSE_SUBTRACT);
  EnumGLIntAddOption(GL_MIN);
  EnumGLIntAddOption(GL_MAX);
};
};
}}
