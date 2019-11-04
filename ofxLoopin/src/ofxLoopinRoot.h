#pragma once

#include "ofxLoopinBuffer.h"
#include "./control/Control.hpp"
#include "ofxLoopinFrame.h"

class ofxLoopinRoot : public ofxLoopin::control::Control, public ofxLoopinHasBuffers {
public:
  // string resolveFilePath( string path );
  ofxLoopinFrame frame;


protected:
  void addRootControls();
};
