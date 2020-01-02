#pragma once
#include "ofMain.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

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
class Window : 
  virtual public ofxLoopin::render::Blit, 
  virtual public ofxLoopin::base::HasInfo 
{
public:
  int width = 0;
  int height = 0;

  // show/ ( string ) - Which buffer to show on screen
  /** loopin/root/show
    type: show
  */
  Show show;
  // osd/ - on-screen display
  /** loopin/root/osd
    type: osd
  */
  OSD osd;

  void setAppBaseWindow( ofAppBaseWindow * window );
  void update();

  void render( const ofxLoopin::clock::Frame & frame, ofxLoopin::base::Buffer * _buffer = nullptr ) {
    // cerr << "Window::render" << endl;

    bool enabled = enable.isEnabledOnce( true );
    if ( !_window && enabled ) {
      createWindow();
    } else if ( _window && !enabled ) {
      destroyWindow();
    }

    if ( _window ) {
      // shared_ptr<ofMainLoop> mainLoop = ofGetMainLoop();
      // if(mainLoop){
      //   mainLoop->setCurrentWindow(_window);
      // }
      // _window->makeCurrent();
      // _window->startRender();
      // renderWindow();
      // _window->finishRender();
      // _window->update();
    }
  };

  void renderWindow() {
    renderReset();
    renderClear();
    renderTexture();
    osd.show = show.getBufferDescription();
    osd.draw();
  };

  // ofTexture * textureToRender() override {
  //   return show.textureToRender();
  // };

  void drawWindow(ofEventArgs & args) {
    renderWindow();
  }

  ofJson infoGet();

protected:
  void patchKey( string key, ofJson & val ) {};
  void patchLocal( const ofJson & value );

  void readLocal( ofJson & value );


  void addSubControls() {
    ofxLoopin::render::Blit::addSubControls();

    addSubControl( "osd", &osd );
    addSubControl( "show", &show );
  };

  void createWindow() {
    if ( _window )
      destroyWindow();

    ofGLFWWindowSettings settings;
    shared_ptr<ofAppBaseWindow> mainWindow = shared_ptr<ofAppBaseWindow>( ofGetWindowPtr() );

    cerr << "Make Window " << mainWindow << endl;

    settings.setGLVersion( root->_glVersionMajor, root->_glVersionMinor );
    settings.setSize( 600, 600 );
    settings.resizable = true;
    settings.shareContextWith = mainWindow;

    cerr << "Make Window" << endl;
    shared_ptr<ofAppBaseWindow> window = ofCreateWindow( settings );
    _window = window.get();
    ofAddListener(_window->events().draw, this, &Window::drawWindow );
  };

  void destroyWindow() {

  };

  void windowToControls() {

  };

  void controlsToWindow() {

  };

  ofAppBaseWindow * _window = nullptr;
  ofPoint _position;

  void sizeFromWindow();
  void sizeToWindow();

};
}};