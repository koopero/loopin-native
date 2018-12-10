#pragma once

#include "ofThread.h"
#include "ofUtils.h"
#include "ofJson.h"

#include "ofxLoopinEvent.h"

#include <iostream>

class ofxLoopinStdio : public ofThread {
public:

  void dispatch( const ofxLoopinEvent & event );

  void start();
  void stop();

  ofJson getValue();


private:
  void threadedFunction();

  void mergeValue (ofJson& a, ofJson& b);

  ofJson value;

private:
  // Json::FastWriter jsonWriter;
  std::vector<string> lines_;
};
