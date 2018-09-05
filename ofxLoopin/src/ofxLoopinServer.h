#pragma once

#include "ofThread.h"
#include "ofxTCPServer.h"
#include "ofxJSON.h"

#include <iostream>

class ofxLoopinServer : public ofThread {
public:
  int16_t port;

  void update();

private:
  void threadedFunction();

  void mergeValue (Json::Value& a, Json::Value& b);

  Json::Value value;
  ofxTCPServer server;
  std::vector<string> buffers;
}
