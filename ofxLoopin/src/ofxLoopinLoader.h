#pragma once

#include "./control/Control.hpp"
#include "ofxLoopinRoot.h"

class ofxLoopinLoader : public ofxLoopin::control::Control {
public:
  virtual void load() {};
  string getFilePath();

protected:
  void patchLocal( const ofJson & value );

  string filePath;
};
