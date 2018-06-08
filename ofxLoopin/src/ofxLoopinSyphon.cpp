#include "ofxLoopinSyphon.h"
#include "ofxJSON.h"

// #ifdef LOOPIN_SYPHON

Json::Value ofxLoopinSyphonRoot::infoGet() {
  Json::Value result;
  result["syphon"] = "here";
  return result;
}

// #endif 