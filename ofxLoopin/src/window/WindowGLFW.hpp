#pragma once
#include "./Window.hpp"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"


namespace ofxLoopin { namespace window {

class WindowGLFW : 
  virtual public Window
{
public:
  void setAppBaseWindow( ofAppBaseWindow * window ) override;

  void onDrawWindow(ofEventArgs & args) {
    renderWindow();
  }

  void render( const ofxLoopin::clock::Frame & frame, ofxLoopin::base::Buffer * _buffer ) override;

protected:
  void createWindow();
  void showWindow();
  void hideWindow();
  void destroyWindow();

  void setFullscreen( int index ) override;

  ofAppGLFWWindow * _windowFW;
};

}}