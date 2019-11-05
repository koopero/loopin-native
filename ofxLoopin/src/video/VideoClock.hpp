#pragma once
#include "../clock/Clock.hpp"
#include "../control/Enum.hpp"

#include "ofMain.h"


namespace ofxLoopin { namespace video {
class VideoClock : public clock::Clock {
public:
  double duration;
  int index;
  int frames;
  control::Enum<ofLoopType, OF_LOOP_NONE> loop;

  void syncIndex( int _index ) {
    if ( index == _index ) {
      _ignoreStale = true;
    }
    index = _index;
    frame.time = (double)_index / rate;
    _syncToFrame = index;
    _syncNext = true;
  }

  void syncTime( double time ) {
    syncIndex( floor( time * (double)rate ) );
  }


  void syncPosition( float position ) {
    position = fmod( position, 1.0 );
    syncIndex( float( frames ) * position );
  }


  bool shouldSync() {
    if ( _syncNext ) {
      _syncNext = false;
      return true;
    }

    return false;
  };

  bool ignoreStale() {
    if ( _ignoreStale ) {
      _ignoreStale = false;
      return true;
    }

    return false;
  }

  int syncFrame() {
    return _syncToFrame;
  }; 

  bool checkEnd() {
    if ( _hasEnded )
      return false;

    if ( speed > 0 && index >= frames - 1 ) 
      _hasEnded = true;

    if ( _hasEnded ) {
      doLoop();
      control::Event event;
      event.type = "end";
      event.data = read();
      dispatch( event );
    }

    return _hasEnded;
  }

  void doLoop() {
    switch( loop.getEnumValue() ) {
      case OF_LOOP_NONE:
        mode.setEnumValue( clock::Frame::Mode::STOP );
        // _syncNext = true;
      break;

      case OF_LOOP_PALINDROME:
        speed = speed * -1;
        _syncNext = true;
      break;

      case OF_LOOP_NORMAL:
        syncIndex( 0 );
      break;
    }
  }

protected:
  bool _syncNext = true;
  bool _ignoreStale = false;
  bool _hasEnded = false;
  int _syncToFrame = -1;

  void addSubControls() override {
    clock::Clock::addSubControls();
    loop.enumAddOption( "none", OF_LOOP_NONE );
    loop.enumAddOption( "loop", OF_LOOP_NORMAL );
    loop.enumAddOption( "normal", OF_LOOP_NORMAL );
    loop.enumAddOption( "palindrome", OF_LOOP_PALINDROME );
    addSubControl( "loop", &loop );
  }

  void readLocal( ofJson & value ) override {
    clock::Clock::readLocal( value );
    value["duration"] = duration;
    value["index"] = index;
  };

  void patchLocal( const ofJson & value ) override  {
    if ( value.is_number() ) {
      syncTime( value.get<double>() );
    }

    if ( value.is_object() ) {
      if ( value.count("time") && value["time"].is_number() ) {
        syncTime( value["time"].get<double>() );
      }

      if ( value.count("position") && value["position"].is_number() ) {
        syncPosition( value["position"].get<double>() );
      }

      if ( ofxLoopinJSONToBool( value, "advance" ) ) {
        running = true;
        // syncIndex( index );
      }

      if ( ofxLoopinJSONToBool( value, "reset" ) ) {
        reset();
        syncTime(0);
      }
    }
  }
};
}};
