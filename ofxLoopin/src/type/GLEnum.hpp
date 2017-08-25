#pragma once

#include "../ofxLoopinControl.h"
#include "./Enum.hpp"

#define EnumGLIntAddOption(I) enumAddOption( "I", I )

namespace ofxLoopin { namespace type {
class GLEnum : public Enum<GLenum,GL_ZERO> {
};
} }
