#pragma once

#include "./control/Control.hpp"
#include "./Enum.hpp"

#define EnumGLIntAddOption(I) enumAddOption( #I, I )

namespace ofxLoopin { namespace type {
class GLEnum : public Enum<GLenum,GL_ZERO> {
};
} }
