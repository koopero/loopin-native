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
  virtual public ofxLoopin::render::Blit
{
public:
  Show show;
  OSD osd;
  control::Int fullscreen = 0;
  control::Bool cursor = true;
  string title;


  void setAppBaseWindow( ofAppBaseWindow * window );
  void update() override;

  void render( const ofxLoopin::clock::Frame & frame, ofxLoopin::base::Buffer * _buffer = nullptr ) override;

  virtual ofTexture * textureToRender() override {
    return nullptr;
  };

  void renderWindow();

  string getWindowDescription();

  // ofTexture * textureToRender() override {
  //   return show.textureToRender();
  // };

  void drawWindow(ofEventArgs & args) {
    renderWindow();
  }

  virtual ofRectangle getBounds() override {
    if ( !_window )
      return ofRectangle(0,0,0,0);

    return ofRectangle(0,0,_window->getWidth(), _window->getHeight() );
  };


protected:
  void addSubControls() override;

  void patchLocal( const ofJson & value ) override;
  void readLocal( ofJson & value ) override;

  void createWindow();
  void showWindow();
  void hideWindow();
  void destroyWindow();

  void windowToControls();
  void controlsToWindow();

  shared_ptr<ofAppGLFWWindow> _window;
  ofPoint _position;

};
}};