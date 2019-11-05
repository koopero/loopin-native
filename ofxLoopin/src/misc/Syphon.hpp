#pragma once

#include "ofMain.h"


#ifdef TARGET_OSX
#define LOOPIN_SYPHON

#include "ofJson.h"
#include "ofxSyphonClient.h"
#include "ofxSyphonServer.h"

#include "../render/Render.hpp"
#include "../base/HasInfo.hpp"

namespace ofxLoopin { namespace misc {
class Syphon : public ofxLoopin::render::Render {
public:
  string app = "Loopin";
  string name;

  
  enum Mode {
    MODE_CLIENT,
    MODE_SERVER,
    MODE_NONE
  };

  ofxLoopin::control::Enum<Mode, MODE_CLIENT> mode;

  void renderBuffer( ofxLoopin::base::Buffer * buffer );
  ofRectangle getBounds();

protected:
  void addSubControls() {
    ofxLoopin::render::Render::addSubControls();
    mode.enumAddOption( "client", MODE_CLIENT );
    mode.enumAddOption( "server", MODE_SERVER );
    mode.enumAddOption( "none", MODE_NONE );

    addSubControl( "mode", &mode );
    addSubControl( "app", new ofxLoopin::control::Value( &app ) );
    addSubControl( "name", new ofxLoopin::control::Value( &name ) );

  }
  
  void maybeOutputBuffer( ofxLoopin::base::Buffer * buffer );


private:
  ofxSyphonServer syphonServer;
	ofxSyphonClient syphonClient;
};

class SyphonRoot : public ofxLoopin::render::Renders<Syphon>, public ofxLoopin::base::HasInfo {
public:
  SyphonRoot() {
    syphonServerDirectory.setup();
  };
  ofJson infoGet();

private: 
  ofxSyphonServerDirectory syphonServerDirectory;  
};
}};

#endif
