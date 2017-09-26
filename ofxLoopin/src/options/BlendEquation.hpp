#pragma once
#include "../type/GLEnum.hpp"

namespace ofxLoopin { namespace options {
class BlendEquation : public type::GLEnum {
protected: void enumAddOptions() {
  enumAddOption("GL_ZERO",GL_ZERO);
  enumAddOption("GL_FUNC_ADD",GL_FUNC_ADD);
  enumAddOption("GL_FUNC_SUBTRACT",GL_FUNC_SUBTRACT);
  enumAddOption("GL_FUNC_REVERSE_SUBTRACT",GL_FUNC_REVERSE_SUBTRACT);
  enumAddOption("GL_MIN",GL_MIN);
  enumAddOption("GL_MAX",GL_MAX);
  // EnumGLIntAddOption(GL_ZERO);
  // EnumGLIntAddOption(GL_ONE);
  // EnumGLIntAddOption(GL_SRC_COLOR);
  // EnumGLIntAddOption(GL_ONE_MINUS_SRC_COLOR);
  // EnumGLIntAddOption(GL_DST_COLOR);
  // EnumGLIntAddOption(GL_ONE_MINUS_DST_COLOR);
  // EnumGLIntAddOption(GL_SRC_ALPHA);
  // EnumGLIntAddOption(GL_ONE_MINUS_SRC_ALPHA);
  // EnumGLIntAddOption(GL_DST_ALPHA);
  // EnumGLIntAddOption(GL_ONE_MINUS_DST_ALPHA);
  // EnumGLIntAddOption(GL_CONSTANT_COLOR);
  // EnumGLIntAddOption(GL_ONE_MINUS_CONSTANT_COLOR);
  // EnumGLIntAddOption(GL_CONSTANT_ALPHA);
  // EnumGLIntAddOption(GL_ONE_MINUS_CONSTANT_ALPHA);
  // EnumGLIntAddOption(GL_SRC_ALPHA_SATURATE);
  // EnumGLIntAddOption(GL_SRC1_COLOR);
  // EnumGLIntAddOption(GL_ONE_MINUS_SRC_COLOR);
  // EnumGLIntAddOption(GL_SRC1_ALPHA);
  // EnumGLIntAddOption(GL_ONE_MINUS_SRC_ALPHA);
};
};
}}
