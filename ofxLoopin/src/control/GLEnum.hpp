#pragma once

#include "./Control.hpp"
#include "./Enum.hpp"

#define EnumGLIntAddOption(I) enumAddOption( #I, I )

namespace ofxLoopin { namespace control {
class GLEnum : public Enum<GLenum,GL_ZERO> {
};
} }
