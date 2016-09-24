#pragma once


#include "ofxLoopinBuffer.h"
#include "ofxLoopinClock.h"
#include "ofxLoopinInput.h"
#include "ofxLoopinFrame.h"
#include "ofxLoopinMap.h"
#include "ofxLoopinRef.h"
#include "ofxLoopinRoot.h"
#include "ofxLoopinReader.h"
#include "ofxLoopinStdio.h"

#include "ofxLoopinImage.h"
#include "ofxLoopinCamera.h"
#include "ofxLoopinKinect.h"
#include "ofxLoopinLayer.h"
#include "ofxLoopinMesh.h"
#include "ofxLoopinOSD.h"
#include "ofxLoopinRender.h"
#include "ofxLoopinSaver.h"
#include "ofxLoopinShaders.h"
#include "ofxLoopinShow.h"
#include "ofxLoopinText.h"
#include "ofxLoopinVideo.h"
#include "ofxLoopinWindow.h"

#include "ofMain.h"

#include "Poco/Path.h"

#include <stdlib.h>

class ofxLoopinApp :
  public ofBaseApp,
  public ofxLoopinRoot,
  public ofxLoopinHasShaders,
  public ofxLoopinHasMeshes,
  public ofxLoopinHasCameras
{
public:
  ofxLoopinApp();
  ofxLoopinApp( int argc, char* argv[] );

  //
  // Root elements, accessible as controls.
  //

  // show/ ( string ) - Which buffer to show on screen
  ofxLoopinShow show;

  // clock/ - Clock parameters
  ofxLoopinClock clock;

  // camera/ - Virtual cameras for 3D transforms
  // ofxLoopinCameras cameras; // defined in ofxLoopinCamera

  // input/ - Input parameters
  ofxLoopinInput input;

  // window/ - Window parameters such as fullscreen
  ofxLoopinWindow window;

  // image/:buffer - Load image files
  ofxLoopinRenders<ofxLoopinImage> images;

  // kinect/:buffer - Kinect 1
  ofxLoopinRenders<ofxLoopinKinect> kinects;

  // test/:buffer - title generator
  ofxLoopinRenders<ofxLoopinText> texts;

  // save/:buffer - saves buffers to image files
  ofxLoopinRenders<ofxLoopinSaver> savers;

  // render/:buffer - renders
  ofxLoopinRenders<ofxLoopinLayer> renders;

  // video/:buffer - video file input
  ofxLoopinRenders<ofxLoopinVideo> videos;

  // osd/ - on-screen display
  ofxLoopinOSD osd;

  // openFrameWorks master overrides.
  void setup ();
  void draw ();

  // Master render function
  void render ();

  // Master event dispatcher.
  // Called by ofxLoopinControl::dispatch
  void dispatch( ofxLoopinEvent & event );

  void update() {
    ofxLoopinControl::update();
  }

protected:
  void updateLocal ();

  void addAppControls() {
    addSubControl( "clock", &clock );
    addSubControl( "input", &input );

    buffers.defaultKey = "output";


    addSubControl( "shader", &shaders );
    shaders.getByKey( "blank", true );
    shaders.defaultKey = "blank";

    // create default mesh, accessible as mesh/sprite/
    addSubControl( "mesh", &meshes );
    meshes.getByKey( "sprite", true );
    meshes.defaultKey = "sprite";

    addSubControl( "camera", &cameras );
    cameras.getByKey( "front", true );
    cameras.defaultKey = "front";

    addSubControl( "read", &reader );

    addSubControl( "image", &images );
    addSubControl( "text", &texts );
    addSubControl( "kinect", &kinects );
    addSubControl( "video", &videos );
    addSubControl( "render", &renders );

    addSubControl( "save", &savers );
    addSubControl( "show", &show );

    addSubControl( "osd", &osd );
    addSubControl( "window", &window );
    window.setAppBaseWindow( ofGetWindowPtr() );
  }

  void addRenderLists () {
    renderLists.push_back( &images );
    renderLists.push_back( &texts );
    renderLists.push_back( &kinects );
    renderLists.push_back( &videos );
    renderLists.push_back( &renders );
    renderLists.push_back( &savers );
  }

  // Utility for reading from stdio
  ofxLoopinStdio stdio;

  // Utility for reading to stdio
  ofxLoopinReader reader;

private:
  int exitAfterFrames = 0;

  vector<ofxLoopinRenderList *> renderLists;
};
