#include "./Window.hpp"

void ofxLoopin::window::Window::addSubControls() {
  ofxLoopin::render::Blit::addSubControls();

  addSubControl( "osd", &osd );
  addSubControl( "show", &show );
};

void ofxLoopin::window::Window::createWindow() {
  if ( _window )
    destroyWindow(); 

  ofGLFWWindowSettings settings;
  shared_ptr<ofAppBaseWindow> mainWindow = shared_ptr<ofAppBaseWindow>( ofGetWindowPtr() );

  cerr << "Make Window " << mainWindow << endl;

  settings.setGLVersion( root->_glVersionMajor, root->_glVersionMinor );
  settings.setSize( 600, 600 );
  settings.resizable = true;
  settings.shareContextWith = mainWindow;

  shared_ptr<ofAppBaseWindow> window = ofCreateWindow( settings );
  _window = std::dynamic_pointer_cast<ofAppGLFWWindow>( window );
  ofAddListener(_window->events().draw, this, &Window::drawWindow );
};

void ofxLoopin::window::Window::showWindow() {
  GLFWwindow* windowP = _window->getGLFWWindow();
  glfwShowWindow(windowP);
};

void ofxLoopin::window::Window::hideWindow() {
  GLFWwindow* windowP = _window->getGLFWWindow();
  glfwHideWindow(windowP);
};

// TODO: Crashes!!
void ofxLoopin::window::Window::destroyWindow() {
  if ( _window ) {
    
    ofRemoveListener(_window->events().draw, this, &Window::drawWindow );

    // _window->close();

    GLFWwindow* windowP = _window->getGLFWWindow();

    glfwSetMouseButtonCallback( windowP, nullptr );
    glfwSetCursorPosCallback( windowP, nullptr );
    glfwSetCursorEnterCallback( windowP, nullptr );
    glfwSetKeyCallback( windowP, nullptr );
    glfwSetWindowSizeCallback( windowP, nullptr );
    glfwSetFramebufferSizeCallback( windowP, nullptr);
    glfwSetWindowCloseCallback( windowP, nullptr );
    glfwSetScrollCallback( windowP, nullptr );
#if GLFW_VERSION_MAJOR>3 || GLFW_VERSION_MINOR>=1
    glfwSetDropCallback( windowP, nullptr );
#endif
    //hide the window before we destroy it stops a flicker on OS X on exit.
    glfwHideWindow(windowP);

    // We must ensure renderer is destroyed *before* glfw destroys the window in glfwDestroyWindow,
    // as `glfwDestroyWindow` at least on Windows has the effect of unloading OpenGL, making all
    // calls to OpenGL illegal.
    // currentRenderer.reset();

    glfwDestroyWindow(windowP);
    windowP = nullptr;
    _window->events().disable();
    // bWindowNeedsShowing = true;

    _window = nullptr;
  }
};


void ofxLoopin::window::Window::patchLocal( const ofJson & value ) {
  // if ( !value.is_object() )
  //   return;

  // if ( !_window )
  //   return;

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
};

void ofxLoopin::window::Window::setAppBaseWindow( ofAppBaseWindow * window ) {
  _window = std::dynamic_pointer_cast<ofAppGLFWWindow>( shared_ptr<ofAppBaseWindow>( window ) );
  if ( _window ) {
    controlsToWindow();
  }
}

void ofxLoopin::window::Window::render( const ofxLoopin::clock::Frame & frame, ofxLoopin::base::Buffer * _buffer ) {
  // cerr << "Window::render" << endl;

  bool enabled = enable.isEnabledOnce( true );
  if ( !_window && enabled ) {
    createWindow();
  } else if ( _window && !enabled ) {
    hideWindow();
  }

};

void ofxLoopin::window::Window::renderWindow() {
  if ( !renderSetup() )
    return;

  ofRectangle bounds = ofRectangle( 0,0, ofGetWindowWidth(), ofGetWindowHeight() );

  renderClear();

  _shader->begin();
  renderUniforms();
  renderStyle();
  show.renderTexture( _shader, bounds );
  // renderSelf();
  resetStyle();
  resetUniforms();
  _shader->end();

  osd.window = getWindowDescription();
  osd.show = show.getBufferDescription();
  osd.draw();
};

string ofxLoopin::window::Window::getWindowDescription() {
  stringstream desc;

  desc << key << " ";
  desc << ofGetWindowWidth() <<"x"<<ofGetWindowHeight();

  return desc.str();
};  


void ofxLoopin::window::Window::readLocal( ofJson & value ) {
  // if ( _window ) {
  //   value["fullscreen"] = (bool) _window->getWindowMode();
  //   value["width"] = width;
  //   value["height"] = height;
  //   value["x"] = _position.x;
  //   value["y"] = _position.y;
  // }
};

// void ofxLoopin::window::Window::sizeFromWindow() {
//   ofPoint size = _window->getWindowSize();
//   width = size.x;
//   height = size.y;
// }

// void ofxLoopin::window::Window::sizeToWindow() {
//   ofPoint size = _window->getWindowSize();

//   int width = ofxLoopin::window::Window::width;
//   int height = ofxLoopin::window::Window::height;

//   width = width <= 0 ? size.x : width;
//   height = height <= 0 ? size.y : height;

//   _window->setWindowShape( width, height );
// }

void ofxLoopin::window::Window::windowToControls() {

}

void ofxLoopin::window::Window::controlsToWindow() {
  bool setSize = false;
  bool setPosition = false;

  float x = box.getX();
  float y = box.getY();
  int width = box.getWidth();
  int height = box.getHeight();

  if ( width && height ) {
    setSize = true;
  }
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

  if ( setSize ) {
    _window->setWindowShape( width, height );
  }

  if ( setPosition ) {
    _window->setWindowPosition( x, y );
  }
}

void ofxLoopin::window::Window::update() {
  ofPoint pos = _window->getWindowPosition();
  ofPoint size = _window->getWindowSize();

  // if ( pos != _position || size.x != width || size.y != height ) {
  //   _position = pos;
  //   sizeFromWindow();
  //   ofxLoopin::control::Event event = ofxLoopin::control::Event("move");
  //   readLocal( event.data );
  //   dispatch( event );
  // }
}
