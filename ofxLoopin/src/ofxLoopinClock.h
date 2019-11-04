#pragma once

#include "ofAppRunner.h"
#include "ofShader.h"

#include "./control/Control.hpp"
#include "./control/Bool.hpp"
#include "./control/Enum.hpp"
#include "./control/Number.hpp"
#include "ofxLoopinFrame.h"

#include "util/ofxLoopinJSON.hpp"

/** loopin/type/clock/sub

speed/:
  type: float
  min: -8
  max: 8
  pow: 2
  default: 1
  markers: [ -1, 0, 1 ]

rate/:
  type: float
  min: 0
  max: 120
  default: 60
  markers: [ 8, 12, 24, 30, 48, 60, 75, 120 ]

mode/:
  type: options
  options:
    - sync
    - async
    - step

advance/:
  type: trigger

*/

class ofxLoopinClock : public ofxLoopin::control::Control {
public:
  ofxLoopinFrame frame;

  static ofxLoopinFrame globalFrame;

  ofxLoopin::control::Enum<ofxLoopinFrame::Mode,ofxLoopinFrame::Mode::TIME> mode;
  ofxLoopin::control::Number rate = 60.0;
  ofxLoopin::control::Number speed = 1.0;

  // ofxLoopin::control::Bool running = true;
  bool running = true;
  double lastTime;

  void advance();
  void advance( const ofxLoopinFrame & parentFrame );
  void reset();


  void seek( double time ) {
    frame.time = time;
    nextDelta = 0;
  };

  bool shouldRender();
  void advanceDelta( double speed );

  void applyUniforms( ofShader & shader );

protected:
  float nextDelta = 0;

  void addSubControls();

  bool isClockGlobal();

  void patchLocal( const ofJson & value );
  void readLocal( ofJson & value );

};
