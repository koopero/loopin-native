#pragma once

#include "ofxLoopinShader.h"
#include "ofxLoopinControlNumeric.h"


class ofxLoopinUniform {
public:
  virtual void bindToShader( ofxLoopinShader * shader ) {};
  virtual void unbind() {};

};

class ofxLoopinUniformFloat :
  public ofxLoopinUniform,
  public ofxLoopinControlNumeric 
{
public:
  void bindToShader( ofxLoopinShader * shader ) {
    float value = getValueFloat();
    shader->shader.setUniform1f( key, value );
  };
};
