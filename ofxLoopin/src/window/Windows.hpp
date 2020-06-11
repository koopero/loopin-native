#pragma once

#include "./Window.hpp"

#ifdef LOOPIN_MULTI_WINDOW

#include "./WindowGLFW.hpp"
#include "../render/Render.hpp"

namespace ofxLoopin { namespace window {
class Windows : 
  public ofxLoopin::render::Renders<WindowGLFW>,
  virtual public base::HasInfo 
{
public:
  ofJson infoGet();

protected:
  void infoGetMonitors( ofJson & result );
  void infoGetGLVersion( ofJson & result );
};
}};

#endif