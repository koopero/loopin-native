#pragma once


#include "ofxLoopinBuffer.h"
#include "./clock/Clock.hpp"
#include "./clock/Frame.hpp"
#include "ofxLoopinInput.h"
#include "./control/Map.hpp"
#include "./control/Reference.hpp"
#include "ofxLoopinRoot.h"
#include "ofxLoopinReader.h"
#include "ofxLoopinStdio.h"

// #include "ofxLoopinAudioAnalyzer.h"
#include "image/Image.hpp"
#include "ofxLoopinCamera.h"
#include "ofxLoopinInfo.h"
#include "kinect/Kinect.hpp"
#include "ofxLoopinLayer.h"
#include "./mesh/Mesh.hpp"
#include "window/OSD.hpp"
#include "ofxLoopinRender.h"
#include "ofxLoopinSaver.h"
#include "./shader/Shaders.hpp"
#include "show/show.hpp"
#include "ofxLoopinText.h"
#include "video/Video.hpp"
#include "pixels/main.hpp"
#include "render/waveform.hpp"
#include "window/Window.hpp"
#include "ofxLoopinSyphon.h"
#include "grabber/Grabber.hpp"


#include "ofMain.h"

#include "boost/filesystem/path.hpp"

#include <stdlib.h>

class ofxLoopinApp :
  public ofBaseApp,
  public ofxLoopinRoot,
  public ofxLoopin::shader::HasShaders,
  public ofxLoopin::mesh::HasMeshes,
  public ofxLoopinHasCameras,
  public ofxLoopinHasUniforms
{
public:
  ofxLoopinApp();
  ofxLoopinApp( int argc, char* argv[] );

  ~ofxLoopinApp() {
    stdio.waitForThread();
  }

  void startFromArgs( int argc, char* argv[] );

  //
  // Root elements, accessible as controls.
  //

  // show/ ( string ) - Which buffer to show on screen
  /** loopin/root/show
    type: show
  */
  ofxLoopin::Show show;

  // clock/ - Clock parameters
  /** loopin/root/clock
    type: clock
  */
  ofxLoopin::clock::Clock clock;

  // input/ - Input parameters
  /** loopin/root/input
    type: input
  */
  ofxLoopinInput input;

  // window/ - Window parameters such as fullscreen
  /** loopin/root/window
    type: window
  */
  ofxLoopin::window::Window window;

  // image/:buffer - Load image files
  /** loopin/root/image
    map: image
  */
  ofxLoopinRenders<ofxLoopinImage> images;

  // kinect/:buffer - Kinect 1
  /** loopin/root/kinect
    map: kinect
  */
  ofxLoopinRenders<ofxLoopin::kinect::Kinect> kinects;

  // text/:buffer
  /** loopin/root/text
    map: text
  */
  ofxLoopinRenders<ofxLoopinText> texts;

  // save/:buffer - saves buffers to image files
  /** loopin/root/save
    map: save
  */
  ofxLoopinRenders<ofxLoopinSaver> savers;

  // render/:buffer - renders
  /** loopin/root/kinect
    map: kinect
  */
  ofxLoopinOrderedRenders<ofxLoopinLayer> renders;

  // pixels/:buffer - pixels
  /** loopin/root/pixels
    map: pixels
  */
  ofxLoopin::pixels::Map pixels;


  // video/:buffer - video file input
  /** loopin/root/video
    map: video
  */
  ofxLoopinRenders<ofxLoopin::video::Video> videos;

  // waveform/:buffer - waveform input ( experimental )
  /** loopin/root/waveform
    map: waveform
  */
  ofxLoopin::render::waveform waveforms;

  // fft/:buffer - ofxFft wrapper.
  /** loopin/root/fft
    map: fft
  */
  // ofxLoopinRenders<ofxLoopinFft> fft;

  // osd/ - on-screen display
  /** loopin/root/osd
    type: osd
  */
  ofxLoopin::window::OSD osd;
  
  #ifdef LOOPIN_SYPHON
  ofxLoopinSyphonRoot syphon;
  #endif

  ofxLoopin::grabber::GrabberList grabbers;


  ofxLoopinInfo info;
  // openFrameWorks master overrides.
  void setup ();
  void draw ();

  // Master render function
  void render ();

  // Master event dispatcher.
  // Called by ofxLoopin::control::Control::dispatch
  void dispatch( ofxLoopin::control::Event & event );

  void update();

protected:
  void updateLocal ();

  void addAppControls() {
    addSubControl( "uniform", &uniforms );

    addSubControl( "clock", &clock );
    addSubControl( "input", &input );

    buffers.defaultKey = "output";


    addSubControl( "shader", &shaders );
    shaders.getByKey( "blank", true );
    shaders.defaultKey = "blank";

    addSubControl( "mesh", &meshes );
    meshes.getByKey( "sprite", true );
    meshes.defaultKey = "sprite";

    addSubControl( "camera", &cameras );
    cameras.getByKey( "front", true );
    cameras.defaultKey = "front";

    addSubControl( "read", &reader );

    addSubControl( "info", &info );

    addSubControl( "image", &images );
    addSubControl( "text", &texts );
    addSubControl( "kinect", &kinects );
    addSubControl( "video", &videos );
    addSubControl( "render", &renders );
    addSubControl( "pixels", &pixels );
    addSubControl( "waveform", &waveforms );
    addSubControl( "grabber", &grabbers );


    #ifdef LOOPIN_SYPHON
    addSubControl( "syphon", &syphon );
    #endif

    addSubControl( "save", &savers );
    addSubControl( "show", &show );

    addSubControl( "osd", &osd );
    addSubControl( "window", &window );

    window.setAppBaseWindow( ofGetWindowPtr() );
  }

  void addRenderLists () {
    renderLists.push_back( &waveforms );
    renderLists.push_back( &images );
    renderLists.push_back( &texts );
    renderLists.push_back( &kinects );
    renderLists.push_back( &videos );
    renderLists.push_back( &grabbers );

    renderLists.push_back( &renders );
    renderLists.push_back( &savers );
    renderLists.push_back( &pixels );

    #ifdef LOOPIN_SYPHON
    renderLists.push_back( &syphon );
    #endif
  }

  // Utility for reading from stdio
  ofxLoopinStdio stdio;

  // Utility for reading to stdio
  ofxLoopinReader reader;

  void keyPressed(int key) {
    // std::cerr << "keyPressed " << key << endl;

    switch ( key ) {
      case OF_KEY_LEFT:
        show.buffer.prev();
      break;

      case OF_KEY_RIGHT:
        show.buffer.next();
      break;
    }
  }

  static ofxLoopin::shader::Shader shaderDefault; 

private:
  int exitAfterFrames = 0;

  std::vector<ofxLoopinRenderList *> renderLists;
};
