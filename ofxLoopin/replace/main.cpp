#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main(int argc, char* argv[]) {
	auto app = new ofApp( argc, argv );

	#ifdef TARGET_OPENGLES
		ofGLESWindowSettings settings;
		settings.glesVersion = 2;
		settings.width = 1280;
		settings.height = 720;
	#else
		ofGLWindowSettings settings;
		settings.setGLVersion(3,2);
	#endif

	ofCreateWindow(settings);     // this kicks off the running of my app
	ofRunApp( app );
}
