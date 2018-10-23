#pragma once

#include "ofxLoopinHasInfo.h"
#include "ofxLoopinControlBool.h"
#include "ofxLoopinControlEnum.h"
#include "ofxLoopinControlNumber.h"
#include "ofxLoopinRender.h"

#include "ofJson.h"

namespace ofxLoopin { namespace grabber {

class Grabber : public ofxLoopinRender {

};

class GrabberList : public ofxLoopinRenders<Grabber>, public ofxLoopinHasInfo {
public:
  ofJson infoGet();  
};

// namespace ofxLoopin::grabber
}};