#pragma once

#include "ofxLoopinBuffer.h"
#include "ofxLoopinClock.h"
#include "ofxLoopinFile.h"
#include "ofxLoopinRender.h"


#include "ofVideoPlayer.h"

class ofxLoopinVideo : public ofxLoopinRender {
public:
  ofxLoopinControlEnum<ofLoopType, OF_LOOP_NONE> loop;
  ofxLoopinClock clock;

protected:
  void patchLocal( const Json::Value & value );
  void patchString( const string & value );

  void renderBuffer( ofxLoopinBuffer * buffer );
  void readLocal( Json::Value & value ) {
    // cerr << "ofxLoopinVideo::readLocal" << endl;
    value["position"] = player.getPosition();
    value["frame"] = player.getCurrentFrame();
  };

  // virtual void readLocal( Json::Value & value ) {};


  void addSubControls() {
    // cerr << "ofxLoopinVideo::addSubControls " << key << endl;

    loop.setEnumKey( "none", OF_LOOP_NONE );
    loop.setEnumKey( "loop", OF_LOOP_NORMAL );
    loop.setEnumKey( "palindrome", OF_LOOP_PALINDROME );

    addSubControl( "loop", &loop );
    addSubControl( "clock", &clock );

  }

private:
  ofVideoPlayer player;

  double getPlayerTime();
  double getPlayerTime( int frame );

};
