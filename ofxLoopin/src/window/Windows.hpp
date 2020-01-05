#pragma once

#include "./Window.hpp"
#include "../render/Render.hpp"

#include "GLFW/glfw3.h"


namespace ofxLoopin { namespace window {

class Windows : 
  public ofxLoopin::render::Renders<Window>, 
  public ofxLoopin::base::HasInfo 
{
public:
  ofJson infoGet() {
    ofJson result;

    infoGetMonitors( result );
    infoGetGLVersion( result );


    return result;
  };
  
  void infoGetMonitors( ofJson & result ) {
    glfwInit();
    int count;
    const auto monitors = glfwGetMonitors(&count);
    for(int i = 0; i<count; i++){
      auto monitor = monitors[i];
      int w,h,x,y;
      float xscale, yscale;

      glfwGetMonitorPhysicalSize(monitor,&w,&h);
      glfwGetMonitorPos(monitor,&x,&y);
      glfwGetMonitorContentScale(monitor,&xscale,&yscale);
      auto mode = glfwGetVideoMode( monitor );
      ofJson monitorJ;
      monitorJ["name"] = glfwGetMonitorName(monitor);
      monitorJ["xscale"] = xscale;
      monitorJ["yscale"] = yscale;
      monitorJ["x"] = x;
      monitorJ["y"] = y;
      monitorJ["widthMM"] = w;
      monitorJ["heightMM"] = h;
      monitorJ["width"] = mode->width;
      monitorJ["height"] = mode->height;
      monitorJ["redBits"] = mode->redBits;
      monitorJ["greenBits"] = mode->greenBits;
      monitorJ["blueBits"] = mode->blueBits;
      monitorJ["refreshRate"] = mode->refreshRate;

      result["monitors"][i] = monitorJ;
    }    
  }

  void infoGetGLVersion( ofJson & result ) {
    shared_ptr<ofBaseGLRenderer> renderer = dynamic_pointer_cast<ofBaseGLRenderer>( ofGetCurrentRenderer() );
    if ( !renderer )
      return;

    bool es = false;

    #ifdef TARGET_OPENGLES
      es = true;
    #endif

    result["gl"]["ES"] = es;
    result["gl"]["VersionMajor"] = renderer->getGLVersionMajor();
    result["gl"]["VersionMinor"] = renderer->getGLVersionMinor();
  }
};
}};
