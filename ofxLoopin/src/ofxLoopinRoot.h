#pragma once



#include "ofxLoopinBuffer.h"
#include "ofxLoopinControl.h"
#include "ofxLoopinFrame.h"


class ofxLoopinRoot : public ofxLoopinControl, public ofxLoopinHasBuffers {
public:
  // string resolveFilePath( string path );
  ofxLoopinFrame frame;


protected:
  void addRootControls();
};
