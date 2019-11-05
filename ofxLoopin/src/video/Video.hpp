#pragma once

#include "../base/Buffer.hpp"
#include "../clock/Clock.hpp"
#include "../base/File.hpp"
#include "../render/Render.hpp"

#include "ofVideoPlayer.h"


#include "./VideoClock.hpp"
#include "./Engine.hpp"

namespace ofxLoopin { namespace video {

typedef Engine<ofVideoPlayer> VideoEngine; 

class Video : public ofxLoopin::render::Render {
public:
  ofxLoopin::control::Enum<ofLoopType, OF_LOOP_NONE> loop;
  VideoClock clock;

protected:
  void patchLocal( const ofJson & value );
  void patchString( string value );

  void renderBuffer( ofxLoopin::base::Buffer * buffer );
  void readLocal( ofJson & value ) {
    value["position"] = engine->getPosition();
    value["frame"] = engine->getCurrentFrame();
  };

  void addSubControls() {
    loop.enumAddOption( "none", OF_LOOP_NONE );
    loop.enumAddOption( "loop", OF_LOOP_NORMAL );
    loop.enumAddOption( "palindrome", OF_LOOP_PALINDROME );

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
