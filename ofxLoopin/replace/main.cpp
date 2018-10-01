#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main(int argc, char* argv[]) {
	auto app = new ofApp( argc, argv );

	#ifdef TARGET_OPENGLES
		ofGLESWindowSettings settings;
		settings.setGLESVersion( 2 );
		settings.setSize( 1280, 720 );
	#else
		ofGLWindowSettings settings;
		settings.setGLVersion(3,2);
	#endif

	ofCreateWindow(settings); 
	ofRunApp( app );
}
