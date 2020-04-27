#pragma once

#include "./ShaderWithUniforms.hpp"
#include ".././control/Map.hpp"

/** loopin/root/shader:
map: shader
*/

namespace ofxLoopin { namespace shader {
class Shaders : public ofxLoopin::control::Map<ShaderWithUniforms> {};

class HasShaders {
public:
  Shaders shaders;
  Shaders * __getMap() { return &shaders; };
};
}};