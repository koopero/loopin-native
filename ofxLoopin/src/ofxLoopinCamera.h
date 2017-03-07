#pragma once

#include "ofxLoopinControl.h"
#include "ofxLoopinControlNumber.h"
#include "ofxLoopinMap.h"
#include "ofxLoopinRoot.h"
#include "ofxLoopinShader.h"
#include "ofxLoopinTransform2D.h"



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

class ofxLoopinCamera : public ofxLoopinControl {
public:
  ofxLoopinControlNumber zoom = ofxLoopinControlNumber(0);
  ofxLoopinControlNumber distance = ofxLoopinControlNumber(1);
  ofxLoopinControlNumber fov = ofxLoopinControlNumber(32);
  ofxLoopinControlNumber dof = ofxLoopinControlNumber(16);
  ofxLoopinControlNumber focus;


  ofxLoopinControlNumber roll;
  ofxLoopinControlNumber pitch;
  ofxLoopinControlNumber yaw;


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

friend class ofxLoopinLayer;
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



  void setTransform( ofxLoopinTransform2D const & _transform ) {
    transform = _transform.makeMatrix( getLayerAspect(), getBufferAspect() );
  }

  void loadMatrixes();


  void setUniforms( ofxLoopinShader * shader ) {
    shader->shader.setUniform1f( "cameraFOV", ofxLoopinCamera::fov );
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
  }
};

class ofxLoopinCameras : public ofxLoopinMap<ofxLoopinCamera> {

};

class ofxLoopinHasCameras {
public:
  ofxLoopinCameras cameras;
  ofxLoopinMap<ofxLoopinCamera> * __getMap() { return &cameras; }
};
