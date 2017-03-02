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

// #include "ofxLoopinAudioAnalyzer.h"
#include "ofxLoopinImage.h"
#include "ofxLoopinCamera.h"
#include "ofxLoopinFft.h"
#include "ofxLoopinKinect.h"
#include "ofxLoopinLayer.h"
#include "ofxLoopinMesh.h"
#include "ofxLoopinOSD.h"
#include "ofxLoopinRender.h"
#include "ofxLoopinPixels.h"
#include "ofxLoopinSaver.h"
#include "ofxLoopinShaders.h"
#include "ofxLoopinShow.h"
#include "ofxLoopinText.h"
#include "ofxLoopinVideo.h"
#include "ofxLoopinWaveform.h"
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
  /** loopin/root/show
    type: show
  */
  ofxLoopinShow show;

  // clock/ - Clock parameters
  /** loopin/root/clock
    type: clock
  */
  ofxLoopinClock clock;

  // camera/ - Virtual cameras for 3D transforms
  // ofxLoopinCameras cameras; // defined in ofxLoopinCamera

  // input/ - Input parameters
  /** loopin/root/input
    type: input
  */
  ofxLoopinInput input;

  // window/ - Window parameters such as fullscreen
  /** loopin/root/window
    type: window
  */
  ofxLoopinWindow window;

  // image/:buffer - Load image files
  /** loopin/root/image
    map: image
  */
  ofxLoopinRenders<ofxLoopinImage> images;

  // kinect/:buffer - Kinect 1
  /** loopin/root/kinect
    map: kinect
  */
  ofxLoopinRenders<ofxLoopinKinect> kinects;

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
  ofxLoopinRenders<ofxLoopinLayer> renders;

  // pixels/:buffer - pixels
  /** loopin/root/pixels
    map: pixels
  */
  ofxLoopinRenders<ofxLoopinPixels> pixels;


  // video/:buffer - video file input
  /** loopin/root/video
    map: video
  */
  ofxLoopinRenders<ofxLoopinVideo> videos;

  // waveform/:buffer - waveform input ( experimental )
  /** loopin/root/waveform
    map: waveform
  */
  ofxLoopinRenders<ofxLoopinWaveform> waveforms;

  // fft/:buffer - ofxFft wrapper.
  /** loopin/root/fft
    map: fft
  */
  ofxLoopinRenders<ofxLoopinFft> fft;

  // osd/ - on-screen display
  /** loopin/root/osd
    type: osd
  */
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
    addSubControl( "pixels", &pixels );
    addSubControl( "waveform", &waveforms );
    addSubControl( "fft", &fft );

    addSubControl( "save", &savers );
    addSubControl( "show", &show );

    addSubControl( "osd", &osd );
    addSubControl( "window", &window );
    window.setAppBaseWindow( ofGetWindowPtr() );
  }

  void addRenderLists () {
    renderLists.push_back( &waveforms );
    renderLists.push_back( &fft );
    renderLists.push_back( &images );
    renderLists.push_back( &texts );
    renderLists.push_back( &kinects );
    renderLists.push_back( &videos );
    renderLists.push_back( &renders );
    renderLists.push_back( &savers );
    renderLists.push_back( &pixels );
  }

  // Utility for reading from stdio
  ofxLoopinStdio stdio;

  // Utility for reading to stdio
  ofxLoopinReader reader;

  void keyPressed(int key) {
    // cerr << "keyPressed " << key << endl;

    switch ( key ) {
      case OF_KEY_LEFT:
        show.buffer.prev();
      break;

      case OF_KEY_RIGHT:
        show.buffer.next();
      break;
    }
  }

private:
  int exitAfterFrames = 0;

  vector<ofxLoopinRenderList *> renderLists;
};
