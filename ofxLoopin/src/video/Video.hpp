#pragma once

#include "ofxLoopinBuffer.h"
#include "./clock/Clock.hpp"
#include "ofxLoopinFile.h"
#include "ofxLoopinRender.h"


#include "ofVideoPlayer.h"
// #include "ofGstVideoPlayer.h"


// #include "./Engine.cpp"
// #include "engine/GstVideoPlayer.h"
// #include "ofxHAPAVPlayer.h"
// #include "ofVideoPlayer.h"
// #include "ofxThreadedVideo.h"


namespace ofxLoopin { namespace video {

// typedef Engine<ofxHAPAVPlayer> VideoEngine; 
// typedef Engine<ofGstVideoPlayer> VideoEngine; 
typedef ofVideoPlayer VideoEngine; 

// typedef Engine<ofAVFoundationPlayer> VideoEngine; 



class Video : public ofxLoopinRender {
public:
  ofxLoopin::control::Enum<ofLoopType, OF_LOOP_NONE> loop;
  ofxLoopin::clock::Clock clock;

protected:
  void patchLocal( const ofJson & value );
  void patchString( string value );

  void renderBuffer( ofxLoopinBuffer * buffer );
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
};
}};
