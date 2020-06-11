#pragma once

#if !defined( TARGET_OF_IOS ) & !defined(TARGET_ANDROID) & !defined(TARGET_EMSCRIPTEN) & !defined(TARGET_RASPBERRY_PI)
#define LOOPIN_MULTI_WINDOW 1 
#endif

#include "ofMain.h"

#include "../render/Blit.hpp"
#include "../base/HasInfo.hpp"
#include "./OSD.hpp"
#include "./Show.hpp"
#include "../util/ofxLoopinJSON.hpp"


/** loopin/type/window

sub/fullscreen:
  type: bool

sub/title:
  type: string

sub/width:
  type: number
  step: 1
  min: 16
  max: 8192
  markers: [ 16, 32, 64, 128, 256, 512, 1024, 1280, 1920, 2048 ]

sub/height:
  type: number
  step: 1
  min: 16
  max: 8192
  markers: [ 16, 32, 64, 128, 256, 512, 720, 1080, 2048 ]
*/

namespace ofxLoopin { namespace window {

class WindowState {
public:
  ofVec2f position;
  ofVec2f size;
  string title;
  int fullscreen = 0;
  bool cursor = false;
  bool vsync = true;

  void setFromWindow( ofAppBaseWindow * window ) {
    position = window->getWindowPosition();
    size = window->getWindowSize();
  }

  bool hasChangedFrom( const WindowState & other ) {
    if ( other.size != size )
      return true;

    if ( other.position != position )
      return true;

    return false;
  }

  void setChanged( const WindowState & other ) {
    position = other.position;
    size = other.size;
    fullscreen = other.fullscreen;
  }
};

class Window : 
  virtual public ofxLoopin::render::Blit
{
public:
  Show show;
  OSD osd;
  control::Int fullscreen = 0;
  control::Bool cursor = true;
  control::Bool vsync = true;

  string title;


  virtual void setAppBaseWindow( ofAppBaseWindow * window );
  
  virtual void render( const ofxLoopin::clock::Frame & frame, ofxLoopin::base::Buffer * _buffer = nullptr ) override;

  virtual ofTexture * textureToRender() override {
    return nullptr;
  };

  void renderWindow();

  string getWindowDescription();

  virtual ofRectangle getBounds() override {
    ofRectangle bounds = ofRectangle(0,0,1024,768);
    bounds = box.getFittedRectangle( bounds );

    return bounds;
  };


protected:
  void addSubControls() override;

  void patchLocalAfter( const ofJson & value ) override;
  // void readLocal( ofJson & value ) override;
  void checkMove();
  void dispatchMove();

  void controlsToState();
  void stateToWindow();

  void stateToControls();

  virtual void setFullscreen( int index );

  ofPoint _position;
  WindowState _state;
  WindowState _windowState;
  bool _windowFresh = true;
  ofAppBaseWindow * _window;
};
}};