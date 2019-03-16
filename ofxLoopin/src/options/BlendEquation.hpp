#pragma once
#include "../type/GLEnum.hpp"

namespace ofxLoopin { namespace options {
class BlendEquation : public type::GLEnum {
protected: void enumAddOptions() {
  enumAddOption("GL_FUNC_ADD",GL_FUNC_ADD);
  enumAddOption("GL_NONE",GL_NONE);
  enumAddOption("GL_ZERO",GL_ZERO);
  enumAddOption("GL_FUNC_SUBTRACT",GL_FUNC_SUBTRACT);
  enumAddOption("GL_FUNC_REVERSE_SUBTRACT",GL_FUNC_REVERSE_SUBTRACT);
  // EnumGLIntAddOption(GL_MIN);
  enumAddOption("GL_MIN",GL_MIN);
  enumAddOption("GL_MAX",GL_MAX);
};
};
}}
