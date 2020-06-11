#include "./Blend.hpp"

const ofJson ofxLoopin::interface::Blend::BLEND_PRESETS = {
  { "none", {
    { "equation", "GL_NONE" },
    { "srcRGB", "GL_ONE" },
    { "srcAlpha", "GL_ONE" },
    { "dstRGB", "GL_ZERO" },
    { "dstAlpha", "GL_ZERO" },
  } },  
  { "alpha", {
    { "equation", "GL_FUNC_ADD" },
    { "srcRGB", "GL_SRC_ALPHA" },
    { "srcAlpha", "GL_SRC_ALPHA" },
    { "dstRGB", "GL_ONE_MINUS_SRC_ALPHA" },
    { "dstAlpha", "GL_ONE_MINUS_SRC_ALPHA" },
  } },
  { "add", {
    { "equation", "GL_FUNC_ADD" },
    { "srcRGB", "GL_ONE" },
    { "srcAlpha", "GL_ONE" },
    { "dstRGB", "GL_ONE" },
    { "dstAlpha", "GL_ONE" },
  } },
  { "alphaadd", {
    { "equation", "GL_FUNC_ADD" },
    { "srcRGB", "GL_SRC_ALPHA" },
    { "srcAlpha", "GL_SRC_ALPHA" },
    { "dstRGB", "GL_ONE" },
    { "dstAlpha", "GL_ONE" },
  } },
  { "max", {
    { "equation", "GL_MAX" },
    { "srcRGB", "GL_ONE" },
    { "srcAlpha", "GL_ONE" },
    { "dstRGB", "GL_ONE" },
    { "dstAlpha", "GL_ONE" },
  } },
  { "min", {
    { "equation", "GL_MIN" },
    { "srcRGB", "GL_ONE" },
    { "srcAlpha", "GL_ONE" },
    { "dstRGB", "GL_ONE" },
    { "dstAlpha", "GL_ONE" },
  } },
  { "mix", {
    { "equation", "GL_FUNC_ADD" },
    { "srcRGB", "GL_CONSTANT_COLOR" },
    { "srcAlpha", "GL_CONSTANT_ALPHA" },
    { "dstRGB", "GL_ONE_MINUS_CONSTANT_COLOR" },
    { "dstAlpha", "GL_ONE_MINUS_CONSTANT_ALPHA" },
  } },
  { "over", {
    { "equation", "GL_FUNC_ADD" },
    { "srcRGB", "GL_ONE" },
    { "srcAlpha", "GL_ONE" },
    { "dstRGB", "GL_ONE_MINUS_SRC_ALPHA" },
    { "dstAlpha", "GL_ONE_MINUS_SRC_ALPHA" },
  } },
};
