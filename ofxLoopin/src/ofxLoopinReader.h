#pragma once

#include "./control/Control.hpp"
#include "ofxLoopinRoot.h"

class ofxLoopinReader : public ofxLoopin::control::Control {
protected:
  void patchString( string value );
};
