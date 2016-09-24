#pragma once

#include "ofxLoopinShader.h"
#include "ofVec2f.h"

class ofxLoopinAspect {
public:
  float mesh;
  float layer;
  float buffer;
  ofVec2f bufferSize;

  void calculate();

  void setUniforms( ofxLoopinShader * shader );

  float toCamera();
  float toTransform();
};
