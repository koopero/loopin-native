#include "ofxLoopinApp.h"

class ofApp : public ofxLoopinApp {
public:
  ofApp() {};
  ofApp( int argc, char* argv[] ) {
    startFromArgs( argc, argv );
  }
};

