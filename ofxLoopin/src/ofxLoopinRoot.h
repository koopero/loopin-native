#pragma once

#include "ofxLoopinBuffer.h"
#include "./control/Control.hpp"
#include "./clock/Frame.hpp"

class ofxLoopinRoot : public ofxLoopin::control::Control, public ofxLoopinHasBuffers {
public:
  // string resolveFilePath( string path );
  ofxLoopin::clock::Frame frame;


protected:
  void addRootControls();
};
