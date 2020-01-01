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

      ofLogNotice() << i << ": " << glfwGetMonitorName(monitor) << ", physical size: " << w << "x" << h << "mm at " << x << ", " << y;
      result["monitors"][i]["name"] = glfwGetMonitorName(monitor);
      result["monitors"][i]["xscale"] = xscale;
      result["monitors"][i]["yscale"] = yscale;
      result["monitors"][i]["x"] = x;
      result["monitors"][i]["y"] = y;
      result["monitors"][i]["widthMM"] = w;
      result["monitors"][i]["heightMM"] = h;
      result["monitors"][i]["width"] = mode->width;
      result["monitors"][i]["height"] = mode->height;
      
    }

    return result;
  };

};
}};
