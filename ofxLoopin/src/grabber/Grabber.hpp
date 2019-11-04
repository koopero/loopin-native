#pragma once

#include "ofxLoopinHasInfo.h"
#include "../control/Number.hpp"
#include "ofxLoopinRender.h"

#include "ofVideoGrabber.h"
#include "ofJson.h"

namespace ofxLoopin { namespace grabber {

class Grabber : public ofxLoopinRender {
public:
  control::Int deviceID = 0;
  control::Int width    = 640;
  control::Int height   = 480;

  void renderBuffer( ofxLoopinBuffer * buffer );
  ofRectangle getBounds();

protected:
  void addSubControls() {
    ofxLoopinRender::addSubControls();

    addSubControl( "width", &width );
    addSubControl( "height", &height );
    addSubControl( "deviceID", &deviceID );
  }

  void refreshSetup();

  int _setupWidth = -1;
  int _setupHeight = -1;
  int _setupDeviceID = -1;

  ofVideoGrabber grabber;
};

class GrabberList : public ofxLoopinRenders<Grabber>, public ofxLoopinHasInfo {
public:
  ofJson infoGet();  
};

// namespace ofxLoopin::grabber
}};