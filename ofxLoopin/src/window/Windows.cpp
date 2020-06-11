#include "./Windows.hpp"
#if defined( LOOPIN_MULTI_WINDOW )
#include "GLFW/glfw3.h"

ofJson ofxLoopin::window::Windows::infoGet() {
  ofJson result;

  infoGetMonitors( result );
  
  return result;
};

void ofxLoopin::window::Windows::infoGetMonitors( ofJson & result ) {
  glfwInit();
  int count;
  const auto monitors = glfwGetMonitors(&count);
  for(int i = 0; i<count; i++){
    auto monitor = monitors[i];
    int w,h,x,y;
    float xscale = 1, yscale = 1;

    glfwGetMonitorPhysicalSize(monitor,&w,&h);
    glfwGetMonitorPos(monitor,&x,&y);

    #if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
      glfwGetMonitorContentScale(monitor,&xscale,&yscale);
    #endif

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

#endif