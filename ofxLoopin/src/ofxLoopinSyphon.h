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
  ofJson infoGet() {
    ofJson result;
    ofJson servers = ofJson::array();
    for ( int i = 0; i < syphonServerDirectory.size(); i ++ ) {
      auto item = syphonServerDirectory.getDescription( i );
      ofJson server;
      server["name"] = item.serverName;
      server["app"] = item.appName;
      servers[i] = server;
    }

    result["servers"] = servers;
    return result;    
  };

private: 
  ofxSyphonServerDirectory syphonServerDirectory;  
};



// #endif
