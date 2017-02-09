#pragma once

#include "ofxFFTLive.h"

#include "ofxLoopinControlEnum.h"
#include "ofxLoopinRender.h"

class ofxLoopinFFT : public ofxLoopinRender {
public:
  void renderBuffer( ofxLoopinBuffer * buffer );

  ofRectangle getBounds();

protected:
  void refresh();
  bool fftIsOpen = false;
  ofxFFTLive fftLive;


  void addSubControls() {
    addSubControl("buffer", &buffer );
  };
};
