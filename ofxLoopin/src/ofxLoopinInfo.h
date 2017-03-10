#pragma once

#include "ofxLoopinControl.h"

class ofxLoopinInfo : public ofxLoopinControl {
protected:
  void readLocal( Json::Value & value );
  Json::Value readSystemInfo();
};

// class ofxLoopinInfoRoot {
// public:
//   ofxLoopinInfo info;
//   ofxLoopinInfo * __getMap() { return &info; }
// };
//
// class ofxLoopinHasInfo {
// protected:
//   void infoRegister();
//   Json::Value info
// }
