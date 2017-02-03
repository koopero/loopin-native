#pragma once

#include "ofxLoopinShaderWithUniforms.h"
#include "ofxLoopinMap.h"

/** loopin/root/shader:
map: shader
*/

class ofxLoopinShaders : public ofxLoopinMap<ofxLoopinShaderWithUniforms> {};

class ofxLoopinHasShaders {
public:
  ofxLoopinShaders shaders;
  ofxLoopinShaders * __getMap() { return &shaders; };
};
