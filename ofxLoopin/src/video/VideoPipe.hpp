#pragma once

#include "../render/Render.hpp"

#include "ofThread.h"

namespace ofxLoopin { namespace video {

class PipeThread : public ofThread {
public :
  void injestFrame( ofFloatPixels pixels );
  void setOutputFrame( ofPixels &frame );
  ofPixels & getInputFrame();

  
  void sendFrame() {

  }
}

class VideoPipe : public ofxLoopin::render::Render {
public:
  control::Enable enable;
  control::Filename file;
  control::Box box;

protected:
  void addSubControls() override {
    addSubControl( "enable", &enable );
    addSubControl( "file", &file  );
    addSubControl( "box", &box  );
  }
};

}}