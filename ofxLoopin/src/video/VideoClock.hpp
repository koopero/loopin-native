#pragma once
#include "../clock/Clock.hpp"

namespace ofxLoopin { namespace video {
class VideoClock : public clock::Clock {
public:
  double duration;
  int index;
  int frames;

  void syncTime( double time ) {
    frame.time = time;
    _syncToFrame = index = floor( time * (double)rate );
    _syncNext = true;
  }

  void syncIndex( int _index ) {
    index = _index;
    frame.time = _index * (double) rate;
    _syncToFrame = index;
    _syncNext = true;
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

  int syncFrame() {
    return _syncToFrame;
  }; 

protected:
  bool _syncNext = true;
  int _syncToFrame = -1;

  void readLocal( ofJson & value ) override {
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
