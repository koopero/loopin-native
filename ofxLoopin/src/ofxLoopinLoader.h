#pragma once

#include "ofxLoopinControl.h"
#include "ofxLoopinRoot.h"

class ofxLoopinLoader : public ofxLoopinControl {
public:
  virtual void load() {};
  string getFilePath();

protected:
  void patchLocal( const Json::Value & value );

  string filePath;
};
