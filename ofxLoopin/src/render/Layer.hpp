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
  ofxLoopin::interface::Blend blend;
  ofxLoopin::control::Enum<GLenum,0> face;

protected:
  void addSubControls() {
    ofxLoopin::render::Blit::addSubControls();

    bool isTop = true;
    addSubControl( "mesh", &mesh );
    addSubControl( "camera", &camera );
    addSubControl( "transform", &transform );

    src = uniforms.tex.getByKey("src", true );
    addSubControl( "src", src );

    /** loopin/type/layer/sub/layer
      map: layer
    */
    addSubControl( "layer", &layers );

    /** loopin/type/layer/sub/face
      options:
        - both
        - front
        - back
    */
    face.enumAddOption("both", 0 );
    face.enumAddOption("front", GL_FRONT );
    face.enumAddOption("back", GL_BACK );
    addSubControl( "face", &face );

    addSubControl( "passes", &passes );
    addSubControl( "pointSize", &pointSize );

    addSubControl( "depth", &depthTest );
    addSubControl( "aspect", &aspect );
    addSubControl( "order", &order );
  }

  bool renderSetup();
  void renderSelf();
  void renderUniforms();
  void renderStyle();
  void renderUniformsPerPass( int pass );

  void resetStyle();
  void resetUniforms();

  ofxLoopin::base::Buffer * _buffer = nullptr;
  ofxLoopin::shader::Shader * _shader = nullptr;
  ofxLoopin::mesh::Mesh * _mesh = nullptr;
  ofxLoopin::render::Camera * _camera = nullptr;

private:
};
}};