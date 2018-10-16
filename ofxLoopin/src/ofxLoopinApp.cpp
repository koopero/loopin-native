#include "ofxLoopinApp.h"

ofxLoopinShader ofxLoopinApp::shaderDefault = ofxLoopinShader("shaderDefault") ;


ofxLoopinApp::ofxLoopinApp () {

}

void ofxLoopinApp::dispatch ( ofxLoopinEvent & event ) {
  stdio.dispatch( event );
}


std::string getcwd_string( void ) {
   return boost::filesystem::current_path().string();
}


ofxLoopinApp::ofxLoopinApp ( int argc, char* argv[] ) {
  startFromArgs( argc, argv );
}

void ofxLoopinApp::startFromArgs( int argc, char* argv[] ) {
  ofxLoopinFile::addPath( getcwd_string() );
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
  ofSetVerticalSync( true );

  #ifdef TARGET_OPENGLES
		ofHideCursor();
	#endif
}

void ofxLoopinApp::update() {
  ofxLoopinControl::update();
}

void ofxLoopinApp::updateLocal() {
  // Take inputs.
  patch( stdio.getValue() );

  clock.advance();
  frame = clock.frame;

  osd.setFrame( frame );

  window.update();

  render();
}



void ofxLoopinApp::draw() {
  ofClear( 12,0,16,255);

  shaderDefault.begin();

  show.draw();

  osd.show = show.getBufferDescription();
  osd.draw();

  shaderDefault.end();


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
