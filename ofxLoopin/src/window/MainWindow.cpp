#include "./MainWindow.hpp"

ofJson ofxLoopin::window::MainWindow::infoGet() {
  ofJson result;

  infoGetMonitors( result );
  infoGetGLVersion( result );

  return result;
};

void ofxLoopin::window::MainWindow::infoGetMonitors( ofJson & result ) {
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

void ofxLoopin::window::MainWindow::infoGetGLVersion( ofJson & result ) {
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