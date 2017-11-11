#pragma once

#include "ofxLoopinControl.h"
#include "ofxLoopinHasInfo.h"
#include "ofxLoopinRoot.h"


class ofxLoopinInfo : public ofxLoopinControl {
protected:
  void readLocal( Json::Value & value );
  Json::Value getInfo();
  Json::Value getInfoKey( const string & key );
};
