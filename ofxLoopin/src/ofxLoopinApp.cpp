#include "ofxLoopinApp.h"

ofxLoopinApp::ofxLoopinApp () {

}

void ofxLoopinApp::dispatch ( ofxLoopinEvent & event ) {
  stdio.dispatch( event );
}


std::string getcwd_string( void ) {
   char buff[PATH_MAX];
   getcwd( buff, PATH_MAX );
   std::string cwd( buff );
   return cwd;
}


ofxLoopinApp::ofxLoopinApp ( int argc, char* argv[] ) {
  ofxLoopinFile::addPath( Poco::Path::forDirectory( getcwd_string() ) );
  ofxLoopinFile::addPath( ofToDataPath("ofxLoopin/", true ) );
}



void ofxLoopinApp::setup () {
  ofDisableArbTex();

  root = this;
  addRootControls();
  addAppControls();
  addRenderLists();

  stdio.start();

  ofSetFrameRate( 60 );
}

void ofxLoopinApp::updateLocal() {
  frame = clock.getFrame();

  // Take inputs.
  patch( stdio.getValue() );
  osd.setFrame( frame );
}


void ofxLoopinApp::draw() {
  render();

  ofClear( 0.05,0,0.1,0);

  show.draw();

  osd.show = show.getBufferDescription();
  osd.draw();

  exitAfterFrames --;
  if ( !exitAfterFrames ) {
    std::exit(0);
  }
}


void ofxLoopinApp::render() {
  ofxLoopinEvent frameEvent = frame.asEvent();
  dispatch( frameEvent );

  for( auto it = renderLists.begin(); it != renderLists.end(); it ++ ) {
    (*it)->render( frame );
  }
}
