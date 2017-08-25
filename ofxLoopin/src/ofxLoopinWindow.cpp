#include "ofxLoopinWindow.h"

void ofxLoopinWindow::setAppBaseWindow( ofAppBaseWindow * window ) {
  _window = window;
  if ( _window ) {
    sizeFromWindow();
  }
}

void ofxLoopinWindow::readLocal( Json::Value & value ) {
  if ( _window ) {
    value["fullscreen"] = (bool) _window->getWindowMode();
    sizeFromWindow();
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

void ofxLoopinWindow::update() {
  ofPoint pos = _window->getWindowPosition();
  if ( pos != _position ) {
    _position = pos;
    ofxLoopinEvent event = ofxLoopinEvent("move");
    readLocal( event.data );
    dispatch( event );
  }
}
