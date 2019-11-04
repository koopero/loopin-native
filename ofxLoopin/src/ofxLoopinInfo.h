#pragma once

#include "./control/Control.hpp"
#include "ofxLoopinHasInfo.h"
#include "ofxLoopinRoot.h"


class ofxLoopinInfo : public ofxLoopin::control::Control {
protected:
  void readLocal( ofJson & value );
  ofJson getInfo();
  ofJson getInfoKey( const string & key );
};
