#pragma once

#include "ofxLoopinControl.h"
#include "ofxLoopinControlNumber.h"
#include "ofxLoopinMap.h"
#include "ofxLoopinRoot.h"
#include "ofxLoopinShader.h"
#include "ofxLoopinTransform2D.h"



#include "ofMatrix4x4.h"
#include "ofCamera.h"


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


  void calculate() {

    model.makeIdentityMatrix();
    // cerr << "camera::getMeshAspect() " << getMeshAspect() << endl;

    model.scale( getMeshAspect(), 1, 1 );


    float fov = ofxLoopinCamera::fov;
    float dist = 1.0 / tanf(PI * fov / 360.0f);

    float zoomLin = pow( 2, zoom );

    view.makeIdentityMatrix();
    view.rotate( yaw, 0, 1, 0 );
    view.rotate( pitch, 1, 0, 0 );
    view.rotate( roll, 0, 0, 1 );

    view.translate( 0, 0, -dist * ofxLoopinCamera::distance );

    float focus = ofxLoopinCamera::focus;
    float dof = ofxLoopinCamera::dof;

    float bufferAspect = getBufferAspect();
    // float bufferAspect = 1.0;
    // cerr << "camera::calculate " << bufferAspect << endl;
    float near = max( 0.001, dist + focus - dof / 2.0 );
    float far = max( 0.001, dist + focus + dof / 2.0 );

    projection.makePerspectiveMatrix( fov, fabs( bufferAspect ), near, far );
    projection.scale( zoomLin, zoomLin, 1 );

    float layerAspect = getLayerAspect();
    // if ( fabs(layerAspect) < fabs(bufferAspect) )
    //   projection.scale( fabs( layerAspect ) / fabs( bufferAspect ), fabs( layerAspect ) / fabs( bufferAspect ), 1 );

    // if ( fabs( aspect ) < 1 )
    //   projection.scale( 1/fabs( aspect ), 1/fabs( aspect ), 1 );

    if ( bufferAspect < 0 ) {
      projection.scale( -1, 1, 1 );
    }

    // cerr << "ofxLoopinCamera::make\n"
    //      << "near:\n" << near << "\n"
    //      << "far:\n" << far << "\n"
    //      << "focus:\n" << focus << "\n"
    //      << "dist:\n" << dist << "\n"
    //      << "view:\n" << view << "\n"
    //      << "model:\n" << model << "\n"
    //      << "projection:\n" << projection
    //      << endl
    // ;

  }

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

  void loadMatrixes( ) {
    auto renderer = ofGetCurrentRenderer();

    renderer->matrixMode( OF_MATRIX_MODELVIEW );
    renderer->loadMatrix( getModelView() );

    renderer->matrixMode( OF_MATRIX_PROJECTION );
    renderer->loadMatrix( getProjection() );
  }


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
