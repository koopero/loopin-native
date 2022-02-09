#pragma once
#include "../control/Enum.hpp"

/** loopin/type/textureWrap:
  type: options
  options:
    - repeat
    - none
    - clamp
*/

namespace ofxLoopin { namespace options {
class Wrap : public ofxLoopin::control::Enum<GLenum,GL_REPEAT> {
protected: void enumAddOptions() {
  EnumGLIntAddOption(GL_REPEAT);
  enumAddOption("repeat", GL_REPEAT);
  enumAddOptionBool( true, GL_REPEAT);

  EnumGLIntAddOption( GL_CLAMP_TO_EDGE );
  enumAddOption("clamp", GL_CLAMP_TO_EDGE );
  enumAddOptionBool( false, GL_CLAMP_TO_EDGE );

  EnumGLIntAddOption(GL_MIRRORED_REPEAT);
  enumAddOption("mirror", GL_MIRRORED_REPEAT);

  #ifndef TARGET_OPENGLES
  EnumGLIntAddOption(GL_CLAMP_TO_BORDER);
  enumAddOption("none",GL_CLAMP_TO_BORDER );
  #endif
};
};
}}
