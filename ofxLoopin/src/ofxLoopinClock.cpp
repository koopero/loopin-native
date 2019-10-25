#include "ofxLoopinClock.h"

ofxLoopinFrame ofxLoopinClock::globalFrame;

void ofxLoopinClock::readLocal( ofJson & value ) {
  value["time"] = frame.time;
}

void ofxLoopinClock::applyUniforms( ofShader & shader ) {
  // cerr << "ClockUniforms " << path << " " << frame.index << endl;
  shader.setUniform1i( "clockIndex", frame.index );
  shader.setUniform1f( "clockTime", frame.timeDayFract() );
  shader.setUniform1f( "clockTimeDays", frame.timeDayWhole() );
  shader.setUniform1f( "clockDelta", frame.delta );
}


void ofxLoopinClock::addSubControls() {
  if ( !isClockGlobal() ) {
    mode.setEnumKey("none", ofxLoopinFrame::Mode::NONE );
    mode.setEnumValue( ofxLoopinFrame::Mode::NONE );
  }

  mode.setEnumKey("time",   ofxLoopinFrame::Mode::TIME );
  mode.setEnumKey("frame",  ofxLoopinFrame::Mode::FRAME );
  mode.setEnumKey("step",   ofxLoopinFrame::Mode::STEP );
  mode.setEnumKey("stop",   ofxLoopinFrame::Mode::STOP );
  mode.setEnumKey("wall",   ofxLoopinFrame::Mode::WALL );

  addSubControl("mode", &mode );
  addSubControl("rate", &rate );
  addSubControl("speed", &speed );
};
bool ofxLoopinClock::isClockGlobal() {
  return ( path == "clock" );
}
void ofxLoopinClock::patchLocal( const ofJson & value ) {
  if ( value.is_number() ) {
    seek( value.get<double>() );
  }

  if ( value.is_object() ) {
    if ( value.count("time") && value["time"].is_number() ) {
      seek( value["time"].get<double>() );
    }

    if ( ofxLoopinJSONToBool( value, "advance") ) {
      running = true;
    }

    if ( ofxLoopinJSONToBool( value, "reset" ) ) {
      reset();
    }
  }

  if ( isClockGlobal() && value.is_object() ) {
    if ( value.count("rate") && value["rate"].is_number() ) {
      ofSetFrameRate( round( value["rate"].get<double>() ) );
    }

    if ( value.count("vsync") ) {
      ofSetVerticalSync( ofxLoopinJSONToBool( value["vsync"] ) );
    }
  }
}


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

  frame.mode = mode.getEnumValue();

  advanceDelta( delta * speed );

  if ( isClockGlobal() ) {
    globalFrame = frame;
  }
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
    case ofxLoopinFrame::Mode::NONE:
      running = true;
      delta = globalFrame.delta;
    break;

    case ofxLoopinFrame::Mode::WALL:
      running = true;
      delta = now - frame.time;
      speed = 1;
    break;

    case ofxLoopinFrame::Mode::TIME:
      running = true;
      delta *= now - lastTime;
    break;

    case ofxLoopinFrame::Mode::FRAME:
      running = true;
      delta *= 1.0 / rate;
    break;

    case ofxLoopinFrame::Mode::STEP:
      running = false;
      delta *= 1.0 / rate;
    break;

    case ofxLoopinFrame::Mode::STOP:
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
