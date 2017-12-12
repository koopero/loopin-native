#pragma once

#include "ofxLoopinShader.h"
#include "ofxLoopinUniforms.h"


class ofxLoopinShaderWithUniforms : public ofxLoopinShader {
public:
  ofxLoopinUniformSet uniforms;

  void applyUniformsSelf() {
    uniforms.bindToShader( this );
  };
  void applyUniformsGlobal() {
    auto has = dynamic_cast<ofxLoopinHasUniforms *> ( root );
    if ( has ) {
      has->uniforms.bindToShader( this );
    }
  };
protected:
  void addSubControls() {
    addSubControl( &uniforms );
    addSubControl("vert", &vert );
    addSubControl("frag", &frag );
  }
};
