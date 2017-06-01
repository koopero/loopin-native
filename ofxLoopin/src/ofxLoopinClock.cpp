#include "ofxLoopinClock.h"

void ofxLoopinClock::reset() {
  frame.time = 0;
  nextDelta = 0;
}

void ofxLoopinClock::advance() {
  double delta = 1;

  if ( !running )
    delta = 0;

  if ( frame.index < 0 ) {
    frame.index = 0;
    frame.time = 0;
    delta = 0;
  } else if ( running ) {
    frame.index ++;
  } else {
    delta = 0;
  }

  advanceDelta( delta * speed );
};

void ofxLoopinClock::advance( const ofxLoopinFrame & parentFrame ) {
  frame.index = parentFrame.index;
  double delta = parentFrame.speed;

  if ( !running )
    delta = 0;

  advanceDelta( delta * speed );
};

void ofxLoopinClock::advanceDelta( double speed ) {
  double delta = nextDelta;
  double now = ofGetSystemTimeMicros() / 1000000.0;

  switch ( mode.getEnumValue() ) {

    case WALL:
      running = true;
      delta = now - frame.time;
      speed = 1;
    break;

    case TIME:
      running = true;
      delta *= now - lastTime;
    break;

    case FRAME:
      running = true;
      delta *= 1.0 / rate;
    break;

    case STEP:
      running = false;
      delta *= 1.0 / rate;
    break;

    case STOP:
      running = false;
    break;
  }

  delta *= speed;

  frame.delta = delta;
  frame.time += delta;
  frame.speed = speed;

  lastTime = now;
  nextDelta = 1;
};
