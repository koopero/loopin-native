#pragma once

#include "ofxLoopinCamera.h"
#include "ofxLoopinControlBool.h"
#include "ofxLoopinClock.h"
#include "ofxLoopinMesh.h"
#include "ofxLoopinRender.h"
#include "ofxLoopinTexture.h"
#include "ofxLoopinTransform2D.h"

#include "ofxLoopinControlNumber.h"

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

class ofxLoopinLayer : public ofxLoopinRender {
public:
  ofxLoopinClock clockControl;
  int passes = 1;
  ofxLoopinControlNumber pointSize;
  ofxLoopinControlBool clear = true;
  ofxLoopinControlBool depthTest = false;

  ofxLoopinTexture * src;
  ofxLoopinTransform2D transform;

  ofxLoopinControlNumber aspect;


  ofxLoopinRef<ofxLoopinCamera,ofxLoopinHasCameras> camera;
  ofxLoopinRef<ofxLoopinMesh,ofxLoopinHasMeshes> mesh;

  ofxLoopinRenders<ofxLoopinLayer> layers;
  ofxLoopinControlEnum<ofBlendMode,OF_BLENDMODE_DISABLED> blend;
  ofxLoopinControlEnum<GLenum,0> face;


  void renderBuffer( ofxLoopinBuffer * buffer );

protected:
  void addSubControls() {
    ofxLoopinRender::addSubControls();

    addSubControl( "shader", &shader );
    addSubControl( "clock", &clockControl );


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
    face.setEnumKey("both", 0 );
    face.setEnumKey("front", GL_FRONT );
    face.setEnumKey("back", GL_BACK );
    addSubControl( "face", &face );

    addSubControl( "passes", new ofxLoopinControlValue( &passes ) );
    addSubControl( "pointSize", &pointSize );
    addSubControl( "clear", &clear );
    addSubControl( "depthTest", &depthTest );


    /** loopin/type/layer/sub/blend
      options:
        - none
        - alpha
        - add
        - subtract
        - multiply
        - screen
    */
    blend.setEnumKey("none", OF_BLENDMODE_DISABLED );
    blend.setEnumKey("alpha", OF_BLENDMODE_ALPHA );
    blend.setEnumKey("add", OF_BLENDMODE_ADD );
    blend.setEnumKey("subtract", OF_BLENDMODE_SUBTRACT );
    blend.setEnumKey("multiply", OF_BLENDMODE_MULTIPLY );
    blend.setEnumKey("screen", OF_BLENDMODE_SCREEN );
    addSubControl( "blend", &blend );

    addSubControl( "aspect", &aspect );

  }

private:
  void renderSelf( ofxLoopinBuffer * buffer, bool isRoot );
};
