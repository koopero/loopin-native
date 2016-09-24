#pragma once

#include "ofxLoopinControl.h"
#include "ofxLoopinRoot.h"

class ofxLoopinReader : public ofxLoopinControl {
protected:
  void patchString( const string & value );
};
