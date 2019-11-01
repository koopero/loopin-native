#pragma once

#include "ofxLoopin::shader::Shader.h"
#include "ofVec2f.h"

class ofxLoopinAspect {
public:
  float mesh;
  float layer;
  float buffer;
  ofVec2f bufferSize;

  void calculate();

  void setUniforms( ofxLoopin::shader::Shader * shader );

  float toCamera();
  float toTransform();
};
