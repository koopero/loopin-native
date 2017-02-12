#pragma once

#include "ofxEasyFft.h"

#include "ofxLoopinControlEnum.h"
#include "ofxLoopinRender.h"

class ofxLoopinFft : public ofxLoopinRender {
public:
  void renderBuffer( ofxLoopinBuffer * buffer );

  ofRectangle getBounds();

protected:
  void refresh();
  ofxEasyFft * fftLive = NULL;


  void addSubControls() {
    ofxLoopinRender::addSubControls();
  };
};
