#pragma once

#include "./Window.hpp"



namespace ofxLoopin { namespace window {

class MainWindow : 
  virtual public Window, 
  virtual public base::HasInfo 
{
public:
  ofJson infoGet();

protected:
  void infoGetGLVersion( ofJson & result );
};
}};
