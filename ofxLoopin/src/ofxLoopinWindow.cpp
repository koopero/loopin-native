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
  }
};

void ofxLoopinWindow::sizeFromWindow() {
  ofPoint size = _window->getWindowSize();
  width = size.x;
  height = size.y;
}
