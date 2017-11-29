#pragma once

//#include "interface/Blend.hpp"


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

  enum Clear {
    NONE,
    RGBA,
    DEPTH,
    BOTH
  };

  ofxLoopinControlEnum<Clear,NONE> clear;
  ofxLoopinControlBool advance = false;
  ofxLoopinControlBool passAdvance = false;
  ofxLoopinControlBool depthTest = false;


  ofxLoopinTexture * src;
  ofxLoopinTransform2D transform;

  ofxLoopinControlNumber aspect;


  ofxLoopinRef<ofxLoopinCamera,ofxLoopinHasCameras> camera;
  ofxLoopinRef<ofxLoopinMesh,ofxLoopinHasMeshes> mesh;

  ofxLoopinRenders<ofxLoopinLayer> layers;
  // ofxLoopin::interface::Blend blend;
  ofxLoopinControlEnum<ofBlendMode,OF_BLENDMODE_DISABLED> blend;
  ofxLoopinControlEnum<GLenum,0> face;


  void renderBuffer( ofxLoopinBuffer * buffer );

protected:
  void addSubControls() {
    ofxLoopinRender::addSubControls();

    bool isTop = true;

    // Find if we're the top layer by checking
    // path length
    // 7 == strlen('render/')
    if ( path.size() > key.size() + 7 )
      isTop = false;

    advance = isTop;
    addSubControl( "advance", &advance );
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

    clear.setEnumKey("none",  NONE  );
    clear.setEnumKey("depth", DEPTH );
    clear.setEnumKey("rgba",  RGBA  );
    clear.setEnumKey("both",  BOTH  );
    clear.setKeyBool( true,   "both" );
    clear.setKeyBool( false,  "none" );
    addSubControl( "clear", &clear );

    addSubControl( "depth", &depthTest );

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

  void renderClear();
  bool renderSetup();
  void renderSelf();
  void renderUniforms();
  void renderStyle();
  void renderUniformsPerPass( int pass );

  void resetStyle();
  void resetUniforms();

  ofxLoopinBuffer * _buffer = nullptr;
  ofxLoopinShader * _shader = nullptr;
  ofxLoopinMesh * _mesh = nullptr;
  ofxLoopinCamera * _camera = nullptr;

private:
};
