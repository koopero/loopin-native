#include "./MainWindow.hpp"

ofJson ofxLoopin::window::MainWindow::infoGet() {
  ofJson result;

  infoGetGLVersion( result );

  return result;
};



void ofxLoopin::window::MainWindow::infoGetGLVersion( ofJson & result ) {
  shared_ptr<ofBaseGLRenderer> renderer = dynamic_pointer_cast<ofBaseGLRenderer>( ofGetCurrentRenderer() );
  if ( !renderer )
    return;

  bool es = false;

  #ifdef TARGET_OPENGLES
    es = true;
  #endif

  result["gl"]["ES"] = es;
  result["gl"]["VersionMajor"] = renderer->getGLVersionMajor();
  result["gl"]["VersionMinor"] = renderer->getGLVersionMinor();
}