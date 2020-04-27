#pragma once

//#include "interface/Blend.hpp"


#include "./Camera.hpp"
#include "../control/Bool.hpp"
#include "../clock/Clock.hpp"
#include "../mesh/Mesh.hpp"
#include "../render/Blit.hpp"
#include "../shader/Texture.hpp"
#include "./Transform2D.hpp"

#include "../control/Number.hpp"
#include "../control/Enable.hpp"
#include "../interface/Blend.hpp"
#include "../shader/Shader.hpp"



#include "ofAppRunner.h"
#include "ofMatrix4x4.h"

/** loopin/type/layer/sub
shader:
  ref: shader

mesh:
  ref: mesh

camera :
  ref: camera

# src:
#   link: ../tex/src

transform:
  type: transform2D

aspect:
  type: float
  min: 0.1
  max: 2
*/

namespace ofxLoopin { namespace render {
class Layer : virtual public Blit {
public:
  ofxLoopin::control::Number pointSize;
  ofxLoopin::control::Number order;
  ofxLoopin::control::Bool passAdvance = false;
  ofxLoopin::control::Bool depthTest = false;
  ofxLoopin::control::Int  passes = 1;

  ofxLoopin::shader::Texture * src;
  ofxLoopin::render::Transform2D transform;

  ofxLoopin::control::Number aspect;

  ofxLoopin::control::Reference<Camera,HasCameras> camera;
  ofxLoopin::control::Reference<ofxLoopin::mesh::Mesh,ofxLoopin::mesh::HasMeshes> mesh;

  ofxLoopin::render::OrderedRenders<Layer> layers;
  ofxLoopin::control::Enum<GLenum,0> face;

protected:
  void addSubControls() override;
  bool renderSetup() override;
  void renderSelf() override;
  void renderUniforms() override;
  void renderStyle() override ;
  void renderUniformsPerPass( int pass );
  void renderAfter() override {
    layers.render( renderingFrame, _buffer );
  };

  ofxLoopin::mesh::Mesh * _mesh = nullptr;
  ofxLoopin::render::Camera * _camera = nullptr;

private:
};
}};