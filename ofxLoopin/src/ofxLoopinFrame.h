#pragma once

#include "ofUtils.h"

#include "./control/Event.hpp"

class ofxLoopinFrame {
public:
  enum Mode {
    TIME,
    FRAME,
    STEP,
    WALL,
    STOP,
    NONE
  };

  int   index = -1;
  float time  = 0.0;
  float delta = 0.0;
  float speed = 1.0;
  Mode  mode  = NONE;

  ofxLoopin::control::Event asEvent();

  bool operator==(const ofxLoopinFrame &other) const {
    return index == other.index;
  };

  bool operator!=(const ofxLoopinFrame &other) const {
    return !(*this == other);
  };

};
