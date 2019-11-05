#pragma once

#include "ofxEasyFft.h"

#include "../control/Enum.hpp"
#include "../render/Render.hpp"

class ofxLoopinFft : public ofxLoopin::render::Render {
public:
  void renderBuffer( ofxLoopin::base::Buffer * buffer );

  ofRectangle getBounds();

protected:
  void refresh();
  ofxEasyFft * fftLive = NULL;


  void addSubControls() {
    ofxLoopin::render::Render::addSubControls();
  };
};
