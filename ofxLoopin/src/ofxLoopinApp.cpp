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
