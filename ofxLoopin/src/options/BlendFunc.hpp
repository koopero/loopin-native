#pragma once
#include "../type/GLEnum.hpp"

namespace ofxLoopin { namespace options {
class BlendFunc : public type::GLEnum {
protected: void enumAddOptions() {
  // std::cerr << "enumAddOptions()" << std::endl;
  enumAddOption("GL_ONE",GL_ONE);
  // EnumGLIntAddOption(GL_ONE);
  // EnumGLIntAddOption(GL_ZERO);

  // GLEnumAddOption(GL_SRC_COLOR);
  // GLEnumAddOption(GL_ONE_MINUS_SRC_COLOR);
  // GLEnumAddOption(GL_DST_COLOR);
  // GLEnumAddOption(GL_ONE_MINUS_DST_COLOR);
  // GLEnumAddOption(GL_SRC_ALPHA);
  // GLEnumAddOption(GL_ONE_MINUS_SRC_ALPHA);
  // GLEnumAddOption(GL_DST_ALPHA);
  // GLEnumAddOption(GL_ONE_MINUS_DST_ALPHA);
  // GLEnumAddOption(GL_CONSTANT_COLOR);
  // GLEnumAddOption(GL_ONE_MINUS_CONSTANT_COLOR);
  // GLEnumAddOption(GL_CONSTANT_ALPHA);
  // GLEnumAddOption(GL_ONE_MINUS_CONSTANT_ALPHA);
  // GLEnumAddOption(GL_SRC_ALPHA_SATURATE);
  // GLEnumAddOption(GL_SRC1_COLOR);
  // GLEnumAddOption(GL_ONE_MINUS_SRC_COLOR);
  // GLEnumAddOption(GL_SRC1_ALPHA);
  // GLEnumAddOption(GL_ONE_MINUS_SRC_ALPHA);
};
};
}}
