#include "./Window.hpp"

ofJson ofxLoopin::window::Window::infoGet() {
  ofJson result;

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

void ofxLoopin::window::Window::setAppBaseWindow( ofAppBaseWindow * window ) {
  _window = window;
  if ( _window ) {
    sizeToWindow();
  }
}

void ofxLoopin::window::Window::readLocal( ofJson & value ) {
  if ( _window ) {
    value["fullscreen"] = (bool) _window->getWindowMode();
    value["width"] = width;
    value["height"] = height;
    value["x"] = _position.x;
    value["y"] = _position.y;

  }
};

void ofxLoopin::window::Window::sizeFromWindow() {
  ofPoint size = _window->getWindowSize();
  width = size.x;
  height = size.y;
}

void ofxLoopin::window::Window::sizeToWindow() {
  ofPoint size = _window->getWindowSize();

  int width = ofxLoopin::window::Window::width;
  int height = ofxLoopin::window::Window::height;

  width = width <= 0 ? size.x : width;
  height = height <= 0 ? size.y : height;

  _window->setWindowShape( width, height );
}

void ofxLoopin::window::Window::update() {
  ofPoint pos = _window->getWindowPosition();
  if ( pos != _position ) {
    _position = pos;
    ofxLoopinEvent event = ofxLoopinEvent("move");
    readLocal( event.data );
    dispatch( event );
  }
}
