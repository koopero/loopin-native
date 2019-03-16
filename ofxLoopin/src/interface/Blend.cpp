#include "./Blend.hpp"

const ofJson ofxLoopin::interface::Blend::BLEND_PRESETS = {
  { "none", {
    { "equation", "none" },
  } },
  { "alpha", {
    { "equation", "GL_FUNC_ADD" },
    { "srcRGB", "GL_ONE" },
    { "srcAlpha", "GL_ONE" },
    { "dstRGB", "GL_ONE" },
    { "dstAlpha", "GL_ONE" },
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
  { "min", {
    { "equation", "GL_MIN" },
    { "srcRGB", "GL_ONE" },
    { "srcAlpha", "GL_ONE" },
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

};
    /** loopin/type/layer/sub/blend
      options:
        - none
        - alpha
        - add
        - subtract
        - multiply
        - screen
    */


    // blend.setEnumKey("none", OF_BLENDMODE_DISABLED );
    // blend.setEnumKey("alpha", OF_BLENDMODE_ALPHA );
    // blend.setEnumKey("add", OF_BLENDMODE_ADD );
    // blend.setEnumKey("subtract", OF_BLENDMODE_SUBTRACT );
    // blend.setEnumKey("multiply", OF_BLENDMODE_MULTIPLY );
    // blend.setEnumKey("screen", OF_BLENDMODE_SCREEN );