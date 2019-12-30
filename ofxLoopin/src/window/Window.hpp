#pragma once
#include "ofMain.h"

#include "../render/Blit.hpp"
#include "../base/HasInfo.hpp"
#include "./OSD.hpp"
#include "./Show.hpp"
#include "../util/ofxLoopinJSON.hpp"


/** loopin/type/window

sub/fullscreen:
  type: bool

sub/title:
  type: string

sub/width:
  type: number
  step: 1
  min: 16
  max: 8192
  markers: [ 16, 32, 64, 128, 256, 512, 1024, 1280, 1920, 2048 ]

sub/height:
  type: number
  step: 1
  min: 16
  max: 8192
  markers: [ 16, 32, 64, 128, 256, 512, 720, 1080, 2048 ]
*/

namespace ofxLoopin { namespace window {
class Window : 
  virtual public ofxLoopin::render::Blit, 
  virtual public ofxLoopin::base::HasInfo 
{
public:
  int width = 0;
  int height = 0;

  // show/ ( string ) - Which buffer to show on screen
  /** loopin/root/show
    type: show
  */
  Show show;
  // osd/ - on-screen display
  /** loopin/root/osd
    type: osd
  */
  OSD osd;

  void setAppBaseWindow( ofAppBaseWindow * window );
  void update();

  void render() {
    // cerr << "renderMain" << endl;
    renderReset();
    ofClear( 12,0,16,255);
    // shader.begin();
    show.draw();
    // shader.end();
    osd.show = show.getBufferDescription();
    osd.draw();
  };

  ofJson infoGet();

protected:
  void patchKey( string key, ofJson & val ) {};
  void patchLocal( const ofJson & value );

  void readLocal( ofJson & value );


  void addSubControls() {
    ofxLoopin::render::Blit::addSubControls();

    addSubControl( "osd", &osd );
    addSubControl( "show", &show );
  };

protected:
  ofAppBaseWindow * _window;
  ofPoint _position;

  void sizeFromWindow();
  void sizeToWindow();

};
}};