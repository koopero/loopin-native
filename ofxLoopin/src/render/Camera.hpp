#pragma once

#include "../control/Control.hpp"
#include "../control/Number.hpp"
#include "../control/Map.hpp"
#include "../base/Root.hpp"
#include "../shader/Shader.hpp"
#include "./Transform2D.hpp"
#include "../control/Vector.hpp"


#include "ofMatrix4x4.h"
#include "ofCamera.h"

/** loopin/type/camera/sub
zoom:
  type: float
  min: -2
  max: 2

distance:
  type: float
  min: -1
  max: 4
  markers:
    - 0
    - 1

fov:
  type: float
  min: 0
  max: 180
  markers:
    - 1
    - 5
    - 15
    - 45
    - 90

dof:
  type: float
  min: 0
  max: 64

focus:
  type: float

roll:
  type: angle

pitch:
  type: angle

yaw:
  type: angle
*/

namespace ofxLoopin { namespace render {

class Layer;

class Camera : public ofxLoopin::control::Control {
public:
  ofxLoopin::control::Number zoom = ofxLoopin::control::Number(0);
  ofxLoopin::control::Number distance = ofxLoopin::control::Number(1);
  ofxLoopin::control::Number fov = ofxLoopin::control::Number(32); 
  ofxLoopin::control::Number dof = ofxLoopin::control::Number(16);
  ofxLoopin::control::Number focus;


  ofxLoopin::control::Number roll;
  ofxLoopin::control::Number pitch;
  ofxLoopin::control::Number yaw;

  ofxLoopin::control::Vector<3> translate;


  ofMatrix4x4 getModel() { return model; };
  ofMatrix4x4 getView() { return view; };
  ofMatrix4x4 getModelView() {
    return model * view;
    // return view * model;
  };

  ofMatrix4x4 getProjection() {
    // return projection;
    return projection * transform;
  };


  void calculate();

friend class ofxLoopin::render::Layer;
private:
  float _aspectBuffer = 0;
  float _aspectMesh = 0;
  float _aspectLayer = 0;

  void setBufferAspect( ofRectangle area, float _override = 0 ) {
    _aspectBuffer = area.getWidth() / area.getHeight() * _override;
  };

  float getBufferAspect() {
    return _aspectBuffer;
  }

  float getMeshAspect() {
    if ( _aspectMesh )
      return _aspectMesh;

    if ( _aspectLayer )
      return _aspectLayer;

    return getBufferAspect();
  }

  float getLayerAspect() {
    if ( _aspectLayer )
      return _aspectLayer;

    return getMeshAspect();
  }

  float getTransformAspect() {
    return getLayerAspect();
  }

  void setMeshAspect( float _override = 0 ) { _aspectMesh = _override; };
  void setLayerAspect( float _override = 0 ) { _aspectLayer = _override; };



  void setTransform( Transform2D const & _transform ) {
    transform = _transform.makeMatrix( getLayerAspect(), getBufferAspect() );
  }

  void loadMatrixes();


  void setUniforms( ofxLoopin::shader::Shader * shader ) {
    shader->shader.setUniform1f( "cameraFOV", Camera::fov );
  }


protected:

  ofMatrix4x4 model;
  ofMatrix4x4 view;
  ofMatrix4x4 projection;
  ofMatrix4x4 transform;

  void addSubControls() {
    addSubControl("zoom", &zoom );
    addSubControl("distance", &distance );
    addSubControl("fov", &fov );
    addSubControl("dof", &dof );

    addSubControl("roll", &roll );
    addSubControl("pitch", &pitch );
    addSubControl("yaw", &yaw );

    addSubControl("translate", &translate );
  }
};

class Cameras : public ofxLoopin::control::Map<Camera> {

};

class HasCameras {
public:
  Cameras cameras;
  ofxLoopin::control::Map<Camera> * __getMap() { return &cameras; }
};
}};