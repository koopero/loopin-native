#pragma once
#include "../control/GLEnum.hpp"

/** loopin/type/textureWrap:
  type: options
  options:
    - repeat
    - none
    - clamp
*/

namespace ofxLoopin { namespace options {
class Wrap : public ofxLoopin::control::GLEnum {
protected: void enumAddOptions() {
  EnumGLIntAddOption(GL_REPEAT);
  enumAddOption("repeat", GL_REPEAT);
  enumAddOptionBool( false, GL_REPEAT);

  EnumGLIntAddOption( GL_CLAMP_TO_EDGE );
  enumAddOption("clamp", GL_CLAMP_TO_EDGE );
  enumAddOptionBool( false, GL_CLAMP_TO_EDGE );

  #ifndef TARGET_OPENGLES
  EnumGLIntAddOption(GL_CLAMP_TO_BORDER);
  enumAddOption("none",GL_CLAMP_TO_BORDER );
  #endif
};
};
}}
