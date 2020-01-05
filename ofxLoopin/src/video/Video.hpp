#pragma once

#include "../base/Buffer.hpp"
#include "../clock/Clock.hpp"
#include "../control/Filename.hpp"

#include "../base/File.hpp"
#include "../render/Render.hpp"

#include "ofVideoPlayer.h"


#include "./VideoClock.hpp"
#include "./Engine.hpp"

namespace ofxLoopin { namespace video {

typedef Engine<ofVideoPlayer> VideoEngine; 

class Video : public ofxLoopin::render::Render {
public:
  control::Filename file;
  VideoClock clock;

protected:
  void patchLocalAfter( const ofJson & value ) override;
  void patchString( string value ) override;

  void renderBuffer( base::Buffer * buffer ) override;

  void addSubControls() override {
    addSubControl( "buffer", &buffer );
    addSubControl( "file", &file );
    addSubControl( "clock", &clock );
    clock.mode.setKey("time");
  }

  bool videoSync();

private:
  VideoEngine * engine = new VideoEngine();
  bool wasLoaded = false;
  bool sendSyncEvent = false;
  void loadFile();
  void setEngine() {
  };
  void onLoaded();
};
}};
