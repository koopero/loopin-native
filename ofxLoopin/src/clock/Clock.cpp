#include "./Clock.hpp"

ofxLoopin::clock::Frame ofxLoopin::clock::Clock::globalFrame;

void ofxLoopin::clock::Clock::readLocal( ofJson & value ) {
  value["time"] = frame.time;
}

void ofxLoopin::clock::Clock::applyUniforms( ofShader & shader ) {
  // cerr << "ClockUniforms " << path << " " << frame.index << endl;
  shader.setUniform1i( "clockIndex", frame.index );
  shader.setUniform1f( "clockTime", frame.time );
  shader.setUniform1f( "clockDelta", frame.delta );
}

void ofxLoopin::clock::Clock::addSubControls() {
  if ( !isClockGlobal() ) {
    mode.enumAddOption("none", Frame::Mode::NONE );
    mode.setEnumValue( Frame::Mode::NONE );
  }

  mode.enumAddOption("time",   Frame::Mode::TIME );
  mode.enumAddOption("frame",  Frame::Mode::FRAME );
  mode.enumAddOption("step",   Frame::Mode::STEP );
  mode.enumAddOption("stop",   Frame::Mode::STOP );
  mode.enumAddOption("wall",   Frame::Mode::WALL );

  addSubControl("mode", &mode );
  addSubControl("rate", &rate );
  addSubControl("speed", &speed );
};

bool ofxLoopin::clock::Clock::isClockGlobal() {
  return ( path == "clock" );
}

void ofxLoopin::clock::Clock::patchLocal( const ofJson & value ) {
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

void ofxLoopin::clock::Clock::reset() {
  frame.time = 0;
  nextDelta = 0;
}

void ofxLoopin::clock::Clock::advance() {
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

void ofxLoopin::clock::Clock::advance( const Frame & parentFrame ) {
  frame.index = parentFrame.index;
  double delta = parentFrame.speed;

  if ( !running )
    delta = 0;

  advanceDelta( delta * speed );
};

void ofxLoopin::clock::Clock::advanceDelta( double speed ) {
  double delta = nextDelta;
  double now = ofGetSystemTimeMicros() / 1000000.0;

  switch ( mode.getEnumValue() ) {
    case Frame::Mode::NONE:
      running = true;
      delta = globalFrame.delta;
    break;

    case Frame::Mode::WALL:
      running = true;
      delta = now - frame.time;
      speed = 1;
    break;

    case Frame::Mode::TIME:
      running = true;
      delta *= now - lastTime;
    break;

    case Frame::Mode::FRAME:
      running = true;
      delta *= 1.0 / rate;
    break;

    case Frame::Mode::STEP:
      running = false;
      delta *= 1.0 / rate;
    break;

    case Frame::Mode::STOP:
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
