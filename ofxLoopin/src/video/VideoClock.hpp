#pragma once
#include "ofxLoopinClock.h"

namespace ofxLoopin { namespace video {
class VideoClock : public ofxLoopinClock {
public:
  double duration;
  int index;

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

  void readLocal( ofJson & value ) {
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
