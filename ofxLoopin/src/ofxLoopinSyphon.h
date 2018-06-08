#pragma once

#warning Is here?
#include "ofMain.h"


#ifdef TARGET_OSX
#warning UMMMMMM
#define LOOPIN_SYPHON 1



#include "ofxJSON.h"
#include "ofxSyphonClient.h"
#include "ofxSyphonServer.h"

#include "ofxLoopinRender.h"
#include "ofxLoopinHasInfo.h"



class ofxLoopinSyphon;

class ofxLoopinSyphonRoot : public ofxLoopinRenders<ofxLoopinSyphon>, public ofxLoopinHasInfo {
public:
  Json::Value infoGet();
};

class ofxLoopinSyphon : public ofxLoopinRender {
public:


private:
  ofxSyphonServer syphonServer;
	ofxSyphonClient syphonClient;
};

#endif
