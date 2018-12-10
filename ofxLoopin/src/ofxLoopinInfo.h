#pragma once

#include "ofxLoopinControl.h"
#include "ofxLoopinHasInfo.h"
#include "ofxLoopinRoot.h"


class ofxLoopinInfo : public ofxLoopinControl {
protected:
  void readLocal( ofJson & value );
  ofJson getInfo();
  ofJson getInfoKey( const string & key );
};
