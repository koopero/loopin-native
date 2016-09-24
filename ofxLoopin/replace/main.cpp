#include "ofMain.h"
#include "ofxLoopinApp.h"

//========================================================================
int main(int argc, char* argv[]) {
	auto app = new ofxLoopinApp( argc, argv );

	ofGLWindowSettings settings;
	settings.setGLVersion(3,2);
	settings.width = 1280;
	settings.height = 720;
	ofCreateWindow(settings);     // this kicks off the running of my app
	ofRunApp( app );
}
