#pragma once

#include "ofUtils.h"
#include "../control/Event.hpp"

namespace ofxLoopin { namespace clock {
class Frame {
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

  bool operator==(const Frame &other) const {
    return index == other.index;
  };

  bool operator!=(const Frame &other) const {
    return !(*this == other);
  };
};
}};