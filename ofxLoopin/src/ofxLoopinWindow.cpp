#include "ofxLoopinWindow.h"

Json::Value ofxLoopinWindow::infoGet() {
  Json::Value result;

  shared_ptr<ofBaseGLRenderer> renderer = dynamic_pointer_cast<ofBaseGLRenderer>( ofGetCurrentRenderer() );

  if ( renderer ) {
    bool es = false;

    #ifdef TARGET_OPENGLES
      es = true;
    #endif

    result["gl"]["ES"] = es;
    result["gl"]["VersionMajor"] = renderer->getGLVersionMajor();
    result["gl"]["VersionMinor"] = renderer->getGLVersionMinor();
  }

  return result;
}

void ofxLoopinWindow::setAppBaseWindow( ofAppBaseWindow * window ) {
  _window = window;
  if ( _window ) {
    sizeToWindow();
  }
}

void ofxLoopinWindow::readLocal( Json::Value & value ) {
  if ( _window ) {
    value["fullscreen"] = (bool) _window->getWindowMode();
    value["width"] = width;
    value["height"] = height;
    value["x"] = _position.x;
    value["y"] = _position.y;

  }
};

void ofxLoopinWindow::sizeFromWindow() {
  ofPoint size = _window->getWindowSize();
  width = size.x;
  height = size.y;
}

void ofxLoopinWindow::sizeToWindow() {
  ofPoint size = _window->getWindowSize();

  int width = ofxLoopinWindow::width;
  int height = ofxLoopinWindow::height;

  width = width <= 0 ? size.x : width;
  height = height <= 0 ? size.y : height;

  _window->setWindowShape( width, height );
}

void ofxLoopinWindow::update() {
  ofPoint pos = _window->getWindowPosition();
  if ( pos != _position ) {
    _position = pos;
    ofxLoopinEvent event = ofxLoopinEvent("move");
    readLocal( event.data );
    dispatch( event );
  }
}
