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

  ofxLoopinControlEnum<Mode, MODE_CLIENT> mode;

  void renderBuffer( ofxLoopinBuffer * buffer );
  ofRectangle getBounds();

protected:
  void addSubControls() {
    ofxLoopinRender::addSubControls();
    mode.setEnumKey( "client", MODE_CLIENT );
    mode.setEnumKey( "server", MODE_SERVER );
    mode.setEnumKey( "none", MODE_NONE );

    addSubControl( "mode", &mode );
    addSubControl( "app", new ofxLoopinControlValue( &app ) );
    addSubControl( "name", new ofxLoopinControlValue( &name ) );

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
