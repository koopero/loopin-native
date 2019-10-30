#pragma once

#include "ofxLoopinBuffer.h"
#include "ofxLoopinClock.h"
#include "ofxLoopinFile.h"
#include "ofxLoopinRender.h"

#include "ofVideoPlayer.h"


#include "./VideoClock.hpp"
#include "./Engine.hpp"

namespace ofxLoopin { namespace video {

typedef Engine<ofVideoPlayer> VideoEngine; 

class Video : public ofxLoopinRender {
public:
  ofxLoopinControlEnum<ofLoopType, OF_LOOP_NONE> loop;
  VideoClock clock;

protected:
  void patchLocal( const ofJson & value );
  void patchString( string value );

  void renderBuffer( ofxLoopinBuffer * buffer );
  void readLocal( ofJson & value ) {
    value["position"] = engine->getPosition();
    value["frame"] = engine->getCurrentFrame();
  };

  void addSubControls() {
    loop.setEnumKey( "none", OF_LOOP_NONE );
    loop.setEnumKey( "loop", OF_LOOP_NORMAL );
    loop.setEnumKey( "palindrome", OF_LOOP_PALINDROME );

    addSubControl( "loop", &loop );

    addSubControl( "clock", &clock );
    clock.mode.setKey("time");

  }

  bool videoSync();

private:
  VideoEngine * engine = new VideoEngine();
  bool wasLoaded = false;
  bool sendSyncEvent = false;
  void loadFile( const string & file );
  void setEngine() {
  };
  void onLoaded();
};
}};
