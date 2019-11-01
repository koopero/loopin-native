#pragma once

#include "./Shader.hpp"
#include "ofxLoopinUniforms.h"


namespace ofxLoopin { namespace shader {
class ShaderWithUniforms : public Shader {
public:
  ofxLoopinUniformSet uniforms;

  void applyUniformsSelf() override {
    uniforms.bindToShader( this );
  };
  void applyUniformsGlobal() override {
    auto has = dynamic_cast<ofxLoopinHasUniforms *> ( root );
    if ( has ) {
      has->uniforms.bindToShader( this );
    }
  };
protected:
  void addSubControls() override {
    addSubControl( &uniforms );
    addSubControl("vert", &vert );
    addSubControl("frag", &frag );
  }
};
}};