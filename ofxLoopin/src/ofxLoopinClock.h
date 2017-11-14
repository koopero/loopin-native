#pragma once

#include "ofAppRunner.h"
#include "ofShader.h"

#include "ofxLoopinControl.h"
#include "ofxLoopinControlBool.h"
#include "ofxLoopinControlEnum.h"
#include "ofxLoopinControlNumber.h"
#include "ofxLoopinFrame.h"


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

class ofxLoopinClock : public ofxLoopinControl {
public:
  ofxLoopinFrame frame;

  static ofxLoopinFrame globalFrame;

  ofxLoopinControlEnum<ofxLoopinFrame::Mode,ofxLoopinFrame::Mode::TIME> mode;
  ofxLoopinControlNumber rate = 60.0;
  ofxLoopinControlNumber speed = 1.0;

  // ofxLoopinControlBool running = true;
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

  void patchLocal( const Json::Value & value );

};
