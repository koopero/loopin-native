#pragma once

#include "./Window.hpp"
#include "GLFW/glfw3.h"


namespace ofxLoopin { namespace window {

class MainWindow : 
  virtual public Window, 
  virtual public base::HasInfo 
{
public:
  ofJson infoGet();

protected:
  void infoGetMonitors( ofJson & result );
  void infoGetGLVersion( ofJson & result );
};
}};
