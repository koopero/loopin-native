#include "./Window.hpp"

void ofxLoopin::window::Window::patchLocal( const ofJson & value ) {
  // if ( !value.is_object() )
  //   return;

  // if ( !_window )
  //   return;

  // // ofxLoopin::control::Event event = ofxLoopin::control::Event("debug");
  // // event.data["_window"] = 3;
  // ofPoint position = _window->getWindowPosition();

  // if ( value.count("fullscreen") ) {
  //   _window->setFullscreen( ofxLoopinJSONToBool( value["fullscreen"] ) );
  // }

  // if ( value.count("cursor") ) {
  //   if ( ofxLoopinJSONToBool( value["cursor"] ) ) {
  //     _window->showCursor();
  //   } else {
  //     _window->hideCursor();
  //   }
  // }

  // #ifndef TARGET_OPENGLES
  //   if ( value.count("title")
  //     && value["title"].is_string()
  //   ) {
  //     _window->setWindowTitle( value["title"].get<std::string>() );
  //   }
  // #endif

  // bool setSize = false;
  // bool setPosition = false;


  // if ( value.count("width")
  //   && value["width"].is_number()
  //   && value["width"].get<int>()
  // ) {
  //   setSize = true;
  //   width = value["width"].get<int>();
  // }

  // if ( value.count("height")
  //   && value["height"].is_number()
  //   && value["height"].get<int>()
  // ) {
  //   setSize = true;
  //   height = value["height"].get<int>();
  // }

  // if ( value.count("x")
  //   && value["x"].is_number()
  // ) {
  //   setPosition = true;
  //   position.x = value["x"].get<int>();
  // }

  // if ( value.count("y")
  //   && value["y"].is_number()
  // ) {
  //   setPosition = true;
  //   position.y = value["y"].get<int>();
  // }

  // if ( setSize ) {
  //   _window->setWindowShape( width, height );
  // }

  // if ( setPosition ) {
  //   _window->setWindowPosition( position.x, position.y );
  // }
};

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
  // if ( _window ) {
  //   value["fullscreen"] = (bool) _window->getWindowMode();
  //   value["width"] = width;
  //   value["height"] = height;
  //   value["x"] = _position.x;
  //   value["y"] = _position.y;
  // }
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
  ofPoint size = _window->getWindowSize();


  if ( pos != _position || size.x != width || size.y != height ) {
    _position = pos;
    sizeFromWindow();
    ofxLoopin::control::Event event = ofxLoopin::control::Event("move");
    readLocal( event.data );
    dispatch( event );
  }
}
