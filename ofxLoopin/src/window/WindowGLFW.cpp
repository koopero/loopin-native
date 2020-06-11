#include "./Window.hpp"

#ifdef LOOPIN_MULTI_WINDOW
#include "./WindowGLFW.hpp"

void ofxLoopin::window::WindowGLFW::setAppBaseWindow( ofAppBaseWindow * window ) {
  _window = window;
  _windowFW = dynamic_cast<ofAppGLFWWindow *>( window );
  _windowFresh = true;
}

void ofxLoopin::window::WindowGLFW::render( const ofxLoopin::clock::Frame & frame, ofxLoopin::base::Buffer * _buffer ) {
  // cerr << "Window::render" << endl;

  bool enabled = enable.isEnabledOnce( true );
  if ( !_window && enabled ) {
    createWindow();
  } else if ( _window && !enabled ) {
    hideWindow();
  }

};

void ofxLoopin::window::WindowGLFW::createWindow() {
  if ( _window )
    destroyWindow(); 

  ofGLFWWindowSettings settings;
  shared_ptr<ofAppBaseWindow> mainWindow = shared_ptr<ofAppBaseWindow>( ofGetWindowPtr() );

  settings.setGLVersion( root->_glVersionMajor, root->_glVersionMinor );

  if ( box.positionIsSet ) 
    settings.setPosition( box.getValueVec2() );

  ofRectangle bounds = getBounds();
  settings.setSize( bounds.width, bounds.height );

  settings.resizable = true;
  settings.shareContextWith = mainWindow;

  shared_ptr<ofAppBaseWindow> window = ofCreateWindow( settings );
  _windowFW = dynamic_cast<ofAppGLFWWindow*>( window.get() );
  ofAddListener( _windowFW->events().draw, this, &WindowGLFW::onDrawWindow );
  _windowFresh = true;
};

void ofxLoopin::window::WindowGLFW::showWindow() {
  GLFWwindow* windowP = _windowFW->getGLFWWindow();
  glfwShowWindow(windowP);
};

void ofxLoopin::window::WindowGLFW::hideWindow() {
  GLFWwindow* windowP = _windowFW->getGLFWWindow();
  glfwHideWindow(windowP);
};

// TODO: Crashes!!
void ofxLoopin::window::WindowGLFW::destroyWindow() {
  if ( _windowFW ) {
    
    ofRemoveListener(_windowFW->events().draw, this, &WindowGLFW::onDrawWindow );
    GLFWwindow* windowP = _windowFW->getGLFWWindow();

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
    _windowFW->events().disable();
    // bWindowNeedsShowing = true;

    _windowFW = nullptr;
  }
};




void ofxLoopin::window::WindowGLFW::setFullscreen( int monitorIndex ) {
  GLFWwindow* window = _windowFW->getGLFWWindow();

  if ( !window ) {
    cerr << "Window fault!" <<endl;
    return;
  }

  int monitorCount;
  const auto monitors = glfwGetMonitors(&monitorCount);

  if ( monitorIndex > monitorCount ) {
    // TODO Error Event
    monitorIndex = 0;
  }

  if ( monitorIndex <= 0 ) {
    glfwSetWindowMonitor(window, NULL, _state.position.x, _state.position.y, _state.size.x, _state.size.x, 0);
  } else {
    auto monitor = monitors[monitorIndex - 1];
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    
    glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
  }
}

#endif