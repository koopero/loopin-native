#pragma once
#include "../type/GLEnum.hpp"

namespace ofxLoopin { namespace options {
class BlendFunc : public type::GLEnum {
protected: void enumAddOptions() {
  EnumGLIntAddOption(GL_ONE);
  EnumGLIntAddOption(GL_ZERO);
  EnumGLIntAddOption(GL_SRC_COLOR);
  EnumGLIntAddOption(GL_ONE_MINUS_SRC_COLOR);
  EnumGLIntAddOption(GL_DST_COLOR);
  EnumGLIntAddOption(GL_ONE_MINUS_DST_COLOR);
  EnumGLIntAddOption(GL_SRC_ALPHA);
  EnumGLIntAddOption(GL_ONE_MINUS_SRC_ALPHA);
  EnumGLIntAddOption(GL_DST_ALPHA);
  EnumGLIntAddOption(GL_ONE_MINUS_DST_ALPHA);
  EnumGLIntAddOption(GL_CONSTANT_COLOR);
  EnumGLIntAddOption(GL_ONE_MINUS_CONSTANT_COLOR);
  EnumGLIntAddOption(GL_CONSTANT_ALPHA);
  EnumGLIntAddOption(GL_ONE_MINUS_CONSTANT_ALPHA);
  EnumGLIntAddOption(GL_SRC_ALPHA_SATURATE);
  EnumGLIntAddOption(GL_ONE_MINUS_SRC_COLOR);
  EnumGLIntAddOption(GL_ONE_MINUS_SRC_ALPHA);

  #ifndef TARGET_OPENGLES
  EnumGLIntAddOption(GL_SRC1_COLOR);
  EnumGLIntAddOption(GL_SRC1_ALPHA);
  #endif
};
};
}}
