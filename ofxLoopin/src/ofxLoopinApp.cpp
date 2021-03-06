#include "ofxLoopinApp.h"

ofxLoopin::shader::Shader ofxLoopinApp::shaderDefault = ofxLoopin::shader::Shader("shaderDefault") ;


ofxLoopinApp::ofxLoopinApp () {

}

void ofxLoopinApp::dispatch ( ofxLoopin::control::Event & event ) {
  stdio.dispatch( event );
}


std::string getcwd_string( void ) {
   return boost::filesystem::current_path().string();
}


ofxLoopinApp::ofxLoopinApp ( int argc, char* argv[] ) {
  startFromArgs( argc, argv );
}

void ofxLoopinApp::startFromArgs( int argc, char* argv[] ) {
  ofxLoopin::base::File::addPath( getcwd_string() );
  ofxLoopin::base::File::addPath( ofToDataPath("ofxLoopin/", true ) );
}


void ofxLoopinApp::setup () {
  ofDisableArbTex();

  root = this;
  addRootControls();
  addAppControls();
  addRenderLists();

  stdio.start();

  ofSetFrameRate( 60 );
  ofSetVerticalSync( true );

  #ifdef TARGET_OPENGLES
		ofHideCursor();
	#endif
}

void ofxLoopinApp::update() {
  ofxLoopin::control::Control::update();
}

void ofxLoopinApp::updateLocal() {
  // Take inputs.
  patch( stdio.getValue() );

  clock.advance();
  frame = clock.frame;

  window.osd.setFrame( frame );
  window.update();

  render();
}



void ofxLoopinApp::draw() {
  window.renderWindow();

  exitAfterFrames --;
  if ( !exitAfterFrames ) {
    std::exit(0);
  }
}


void ofxLoopinApp::render() {
  ofxLoopin::control::Event frameEvent = frame.asEvent();
  dispatch( frameEvent );

  for( auto it = renderLists.begin(); it != renderLists.end(); it ++ ) {
    (*it)->render( frame );
  }
}
