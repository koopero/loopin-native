#pragma once

#include "../base/HasInfo.hpp"
#include "../control/Number.hpp"
#include "../render/Render.hpp"

#include "ofVideoGrabber.h"
#include "ofJson.h"

namespace ofxLoopin { namespace grabber {

class Grabber : public ofxLoopin::render::Render {
public:
  control::Int deviceID = 0;
  control::Int width    = 640;
  control::Int height   = 480;

  void renderBuffer( ofxLoopin::base::Buffer * buffer );
  ofRectangle getBounds();

protected:
  void addSubControls() {
    ofxLoopin::render::Render::addSubControls();

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

class GrabberList : public ofxLoopin::render::Renders<Grabber>, public ofxLoopin::base::HasInfo {
public:
  ofJson infoGet();  
};

// namespace ofxLoopin::grabber
}};