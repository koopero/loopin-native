#pragma once

#include "ofThread.h"
#include "ofUtils.h"
#include "ofJson.h"

#include "./control/Event.hpp"

#include <iostream>

class ofxLoopinStdio : public ofThread {
public:

  void dispatch( const ofxLoopin::control::Event & event );

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
