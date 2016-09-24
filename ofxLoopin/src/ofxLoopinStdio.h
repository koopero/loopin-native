#pragma once

#include "ofThread.h"
#include "ofUtils.h"

#include "ofxJSON.h"

#include "ofxLoopinEvent.h"

#include <iostream>

class ofxLoopinStdio : public ofThread {
public:

  void dispatch( const ofxLoopinEvent & event );

  void start();
  void stop();

  Json::Value getValue();


private:
  void threadedFunction();

  void mergeValue (Json::Value& a, Json::Value& b);

  Json::Value value;

private:
  Json::FastWriter jsonWriter;
  vector<string> lines_;
};
