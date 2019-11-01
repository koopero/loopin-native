#pragma once

#include "./ShaderWithUniforms.hpp"
#include "../ofxLoopinMap.h"

/** loopin/root/shader:
map: shader
*/

namespace ofxLoopin { namespace shader {
class Shaders : public ofxLoopinMap<ShaderWithUniforms> {};

class HasShaders {
public:
  Shaders shaders;
  Shaders * __getMap() { return &shaders; };
};
}};