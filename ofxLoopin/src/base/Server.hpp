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

  void mergeValue (ofJson& a, ofJson& b);

  ofJson value;
  ofxTCPServer server;
  std::vector<string> buffers;
}
