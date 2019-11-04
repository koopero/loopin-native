#pragma once

#include "ofMain.h"


#ifdef TARGET_OSX
#define LOOPIN_SYPHON

#include "ofJson.h"
#include "ofxSyphonClient.h"
#include "ofxSyphonServer.h"

#include "ofxLoopinRender.h"
#include "ofxLoopinHasInfo.h"

class ofxLoopinSyphon : public ofxLoopinRender {
public:
  string app = "Loopin";
  string name;

  
  enum Mode {
    MODE_CLIENT,
    MODE_SERVER,
    MODE_NONE
  };

  ofxLoopin::control::Enum<Mode, MODE_CLIENT> mode;

  void renderBuffer( ofxLoopinBuffer * buffer );
  ofRectangle getBounds();

protected:
  void addSubControls() {
    ofxLoopinRender::addSubControls();
    mode.enumAddOption( "client", MODE_CLIENT );
    mode.enumAddOption( "server", MODE_SERVER );
    mode.enumAddOption( "none", MODE_NONE );

    addSubControl( "mode", &mode );
    addSubControl( "app", new ofxLoopin::control::Value( &app ) );
    addSubControl( "name", new ofxLoopin::control::Value( &name ) );

  }
  
  void maybeOutputBuffer( ofxLoopinBuffer * buffer );


private:
  ofxSyphonServer syphonServer;
	ofxSyphonClient syphonClient;
};

class ofxLoopinSyphonRoot : public ofxLoopinRenders<ofxLoopinSyphon>, public ofxLoopinHasInfo {
public:
  ofxLoopinSyphonRoot() {
    syphonServerDirectory.setup();
  };
  ofJson infoGet();

private: 
  ofxSyphonServerDirectory syphonServerDirectory;  
};



#endif
