#include "./Window.hpp"

void ofxLoopin::window::Window::setAppBaseWindow( ofAppBaseWindow * window ) {
  _window = window;
  _windowFresh = true;
}


void ofxLoopin::window::Window::addSubControls() {
  ofxLoopin::render::Blit::addSubControls();

  addSubControl( "title", new ofxLoopin::control::Value( &title ) );
  addSubControl( "osd", &osd );
  addSubControl( "show", &show );
  addSubControl( "fullscreen", &fullscreen );
  addSubControl( "cursor", &cursor );
};

void ofxLoopin::window::Window::patchLocalAfter( const ofJson & value ) {
  controlsToState();
};

void ofxLoopin::window::Window::render( const ofxLoopin::clock::Frame & frame, ofxLoopin::base::Buffer * _buffer ) {
  // cerr << "Window::render" << endl;
};

void ofxLoopin::window::Window::renderWindow() {
  if ( !renderSetup() )
    return;

  stateToWindow();
  checkMove();
  _windowFresh = false;

  ofRectangle bounds = ofRectangle( 0,0, ofGetWindowWidth(), ofGetWindowHeight() );

  renderClear();

  _shader->begin();
  renderUniforms();
  renderStyle();
  show.renderTexture( _shader, bounds );
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

void ofxLoopin::window::Window::controlsToState() {
  if ( box.positionIsSet )
    _state.position = box.getXY();

  _state.size = box.getZW();
  _state.fullscreen = fullscreen;
  _state.title = title;
  _state.vsync = vsync;
}

void ofxLoopin::window::Window::stateToWindow() {
  if ( _state.position != _windowState.position ) {
    _window->setWindowPosition( _state.position.x, _state.position.y );
    _windowState.position = _state.position;
  }

  if ( _state.size != _windowState.size && _state.size.x >= 1 && _state.size.y >= 1 ) {
    _window->setWindowShape( _state.size.x, _state.size.y );
    _windowState.size = _state.size;
  }

  if ( _state.cursor != _windowState.cursor ) {
    if ( _state.cursor ) {
      _window->showCursor();
    } else {
      _window->hideCursor();
    }
    _windowState.cursor = _state.cursor;
  }

  if ( _state.fullscreen != _windowState.fullscreen ) {
    setFullscreen( _state.fullscreen );
    _windowState.fullscreen = _state.fullscreen;
  }

  if ( _state.vsync != _windowState.vsync ) {
    _window->setVerticalSync( _state.vsync );
    _windowState.vsync = _state.vsync;
  }

  if ( _state.title != _windowState.title ) {
    _window->setWindowTitle( _state.title );
    _windowState.title = _state.title;
  }
}


void ofxLoopin::window::Window::stateToControls() {
  box.setXY( _state.position );
  box.setZW( _state.size );
}

void ofxLoopin::window::Window::checkMove() {
  if ( !_window )
    return;

  _windowState.setFromWindow( _window );

  if ( _windowState.hasChangedFrom( _state ) ) {
    _state.setChanged( _windowState );
    stateToControls();
    dispatchMove();
  }

  controlsToState();
}

void ofxLoopin::window::Window::dispatchMove() {
  ofxLoopin::control::Event event = ofxLoopin::control::Event("move");
  event.data["x"] = _state.position.x;
  event.data["y"] = _state.position.y;
  event.data["w"] = _state.size.x;
  event.data["h"] = _state.size.y;
  dispatch( event );
}


void ofxLoopin::window::Window::setFullscreen( int monitorIndex ) {
  _window->setFullscreen( monitorIndex > 0 );
}