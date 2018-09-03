#pragma once

#include "ofxLoopinBuffer.h"
#include "ofxLoopinClock.h"
#include "ofxLoopinFile.h"
#include "ofxLoopinRender.h"


#include "ofVideoPlayer.h"

#include "./Engine.cpp"
#include "ofxHAPAVPlayer.h"

namespace ofxLoopin { namespace video {

typedef Engine<ofxHAPAVPlayer> VideoEngine; 

class Video : public ofxLoopinRender {
public:
  ofxLoopinControlEnum<ofLoopType, OF_LOOP_NONE> loop;
  ofxLoopinClock clock;

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
  }

  bool videoSync();

private:
  VideoEngine * engine;
  bool wasLoaded = false;
};
}};
