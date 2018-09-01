#pragma once

#include "ofMain.h"


// #ifdef TARGET_OSX
#define LOOPIN_SYPHON

#include "ofJson.h"
#include "ofxSyphonClient.h"
#include "ofxSyphonServer.h"

#include "ofxLoopinRender.h"
#include "ofxLoopinHasInfo.h"

class ofxLoopinSyphon : public ofxLoopinRender {
public:

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



// #endif
