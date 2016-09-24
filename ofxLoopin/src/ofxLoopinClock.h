#pragma once

#include "ofxLoopinControl.h"
#include "ofxLoopinControlEnum.h"
#include "ofxLoopinControlNumeric.h"



class ofxLoopinClock : public ofxLoopinControl {
public:
  ofxLoopinFrame frame;

  static ofxLoopinFrame globalFrame;

  enum Mode {
    ASYNC,
    SYNC,
    STEP
  };

  ofxLoopinControlEnum<Mode,ASYNC> mode;
  ofxLoopinControlNumeric rate;
  ofxLoopinControlNumeric speed;

  bool running = true;

  double lastTime;

  ofxLoopinFrame getFrame() {
    double delta = nextDelta;
    double now = ofGetSystemTimeMicros() / 1000000.0;

    if ( frame.index < 0 ) {
      frame.index = 0;
      frame.time = 0;
      delta *= 0;
    } else if ( running ) {
      frame.index ++;
    } else {
      delta *= 0;
    }

    switch ( mode.getEnumValue() ) {
      case SYNC:
        delta *= now - lastTime;
      break;

      case STEP:
        running = false;
      case ASYNC:
        delta *= 1.0 / rate.getValueFloat();
      break;
    }

    float _speed = speed.getValueFloat();
    delta *= _speed;

    frame.delta = delta;
    frame.time += delta;
    frame.speed = _speed;

    lastTime = now;
    nextDelta = 1;

    return frame;
  };

  void seek( double time ) {
    frame.time = time;
    nextDelta = 0;
  };

  bool shouldRender();


protected:

  float nextDelta = 1.0;

  void addSubControls() {
    mode.setEnumKey("async", ASYNC );
    mode.setEnumKey("sync", SYNC );
    mode.setEnumKey("step", STEP );

    addSubControl("mode", &mode );

    rate.setValueHard( 60.0 );
    addSubControl("rate", &rate );

    speed.setValueHard( 1.0 );
    addSubControl("speed", &speed );
  };

  void patchLocal( const Json::Value & value ) {
    if ( value.isNumeric() ) {
      seek( value.asDouble() );
    }

    if ( value.isObject() ) {
      if ( value.isMember("advance") && value["advance"].asBool() ) {
        running = true;
      }
    }
  }

};
