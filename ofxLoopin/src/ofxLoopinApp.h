#pragma once


#include "./base/Buffer.hpp"
#include "./clock/Clock.hpp"
#include "./clock/Frame.hpp"
#include "./base/Input.hpp"
#include "./control/Map.hpp"
#include "./control/Reference.hpp"
#include "./base/Root.hpp"
#include "./base/Reader.hpp"
#include "./base/Stdio.hpp"

// #include "ofxLoopinAudioAnalyzer.h"
#include "./image/Image.hpp"
#include "./render/Camera.hpp"
#include "./base/Info.hpp"
#include "./kinect/Kinect.hpp"
#include "./render/Layer.hpp"
#include "./mesh/Mesh.hpp"
#include "./render/Render.hpp"
#include "./image/Saver.hpp"
#include "./shader/Shaders.hpp"
#include "./misc/Text.hpp"
#include "./video/Video.hpp"
#include "./pixels/Render.hpp"
#include "./audio/waveform.hpp"
#include "./window/MainWindow.hpp"
#include "./window/Windows.hpp"
#include "./misc/Syphon.hpp"
#include "./grabber/Grabber.hpp"
#include "./blobs/Blobs.hpp"



#include "ofMain.h"

#include "boost/filesystem/path.hpp"

#include <stdlib.h>

class ofxLoopinApp :
  public ofBaseApp,
  public ofxLoopin::base::Root,
  public ofxLoopin::shader::HasShaders,
  public ofxLoopin::mesh::HasMeshes,
  public ofxLoopin::render::HasCameras,
  public ofxLoopin::shader::HasUniforms
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


  // clock/ - Clock parameters
  /** loopin/root/clock
    type: clock
  */
  ofxLoopin::clock::Clock clock;

  // input/ - Input parameters
  /** loopin/root/input
    type: input
  */
  ofxLoopin::base::Input input;

  // window/ - Window parameters such as fullscreen
  /** loopin/root/window
    type: window
  */
  ofxLoopin::window::MainWindow window;
  ofxLoopin::window::Windows windows;

  // image/:buffer - Load image files
  /** loopin/root/image
    map: image
  */
  ofxLoopin::render::Renders<ofxLoopin::image::Image> images;

  // kinect/:buffer - Kinect 1
  /** loopin/root/kinect
    map: kinect
  */
  ofxLoopin::render::Renders<ofxLoopin::kinect::Kinect> kinects;

  // text/:buffer
  /** loopin/root/text
    map: text
  */
  ofxLoopin::render::Renders<ofxLoopin::misc::Text> texts;

  // save/:buffer - saves buffers to image files
  /** loopin/root/save
    map: save
  */
  ofxLoopin::render::Renders<ofxLoopin::image::Saver> savers;
  
  ofxLoopin::render::Renders<ofxLoopin::blobs::Blobs> blobs;

  // render/:buffer - renders
  /** loopin/root/kinect
    map: kinect
  */
  ofxLoopin::render::OrderedRenders<ofxLoopin::render::Layer> renders;

  // pixels/:buffer - pixels
  /** loopin/root/pixels
    map: pixels
  */
  ofxLoopin::pixels::Map pixels;


  // video/:buffer - video file input
  /** loopin/root/video
    map: video
  */
  ofxLoopin::render::Renders<ofxLoopin::video::Video> videos;

  // waveform/:buffer - waveform input ( experimental )
  /** loopin/root/waveform
    map: waveform
  */
  ofxLoopin::render::waveform waveforms;

  // fft/:buffer - ofxFft wrapper.
  /** loopin/root/fft
    map: fft
  */
  // ofxLoopin::render::Renders<ofxLoopinFft> fft;

  
  #ifdef LOOPIN_SYPHON
  ofxLoopin::misc::SyphonRoot syphon;
  #endif

  ofxLoopin::grabber::GrabberList grabbers;


  ofxLoopin::base::Info info;
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
    addSubControl( "blobs", &blobs );

    addSubControl( "show", &(window.show) );
    addSubControl( "osd", &(window.osd) );
    addSubControl( "window", &window );
    addSubControl( "windows", &windows );


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
    renderLists.push_back( &windows );
    renderLists.push_back( &blobs );
    renderLists.push_back( &savers );
    renderLists.push_back( &pixels );

    #ifdef LOOPIN_SYPHON
    renderLists.push_back( &syphon );
    #endif
  }

  // Utility for reading from stdio
  ofxLoopin::base::Stdio stdio;

  // Utility for reading to stdio
  ofxLoopin::base::Reader reader;

  void keyPressed(int key) {
    // std::cerr << "keyPressed " << key << endl;

    switch ( key ) {
      case OF_KEY_LEFT:
        window.show.buffer.prev();
      break;

      case OF_KEY_RIGHT:
        window.show.buffer.next();
      break;
    }
  }

  static ofxLoopin::shader::Shader shaderDefault; 

private:
  int exitAfterFrames = 0;

  std::vector<ofxLoopin::render::RenderList *> renderLists;
};
