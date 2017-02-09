#pragma once

#include "ofSoundStream.h"

#include "ofxLoopinControlEnum.h"
#include "ofxLoopinRender.h"

class ofxLoopinWaveform : public ofxLoopinRender, public ofBaseSoundInput {
public:
  void renderBuffer( ofxLoopinBuffer * buffer );
  void audioIn(ofSoundBuffer &buffer);

  ofRectangle getBounds();

protected:
  bool streamIsOpen = false;
  ofSoundStream soundStream;
  ofSoundBuffer samples;
  // void patchLocal( const Json::Value & value );
  // void patchString( const string & value );

  void addSubControls() {
    addSubControl("buffer", &buffer );
  };
};
