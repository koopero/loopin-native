#pragma once

#include "ofUtils.h"

#include "ofxLoopinEvent.h"

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

  int    index = -1;
  double time  = 0.0;
  float  delta = 0.0;
  float  speed = 1.0;
  Mode  mode  = NONE;

  ofxLoopinEvent asEvent();

  bool operator==(const ofxLoopinFrame &other) const {
    return index == other.index;
  };

  bool operator!=(const ofxLoopinFrame &other) const {
    return !(*this == other);
  };

  double timeDayFract() {
    return std::fmod( time, 24*60*60 );
  };

  float timeDayWhole() {
    return floor( time / (24*60*60) );
  }
};
