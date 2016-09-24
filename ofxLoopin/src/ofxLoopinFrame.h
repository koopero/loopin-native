#pragma once

#include "ofUtils.h"

#include "ofxLoopinEvent.h"

class ofxLoopinFrame {
public:
  int   index = -1;
  float time  = 0.0;
  float delta = 0.0;
  float speed = 1.0;

  ofxLoopinEvent asEvent();
};
