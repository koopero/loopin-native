#pragma once

#include "ofMain.h"

#include "ofxLoopinControl.h"
#include "ofxLoopinHasInfo.h"

#include "util/ofxLoopinJSON.hpp"


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

class ofxLoopinWindow : public ofxLoopinControl, public ofxLoopinHasInfo {
public:
  int width = 0;
  int height = 0;

  void setAppBaseWindow( ofAppBaseWindow * window );
  void update();

  ofJson infoGet();

protected:
  void patchKey( string key, ofJson & val ) {};
  void patchLocal( const ofJson & value ) {

    ofxLoopinEvent event = ofxLoopinEvent("debug");

    event.data["_window"] = 3;

    ofPoint position = _window->getWindowPosition();

    if ( !value.is_object() )
      return;

    if ( !_window )
      return;

    if ( value.count("fullscreen") ) {
      _window->setFullscreen( ofxLoopinJSONToBool( value["fullscreen"] ) );
    }

    if ( value.count("cursor") ) {
      if ( ofxLoopinJSONToBool( value["cursor"] ) ) {
        _window->showCursor();
      } else {
        _window->hideCursor();
      }
    }

    #ifndef TARGET_OPENGLES
      if ( value.count("title")
        && value["title"].is_string()
      ) {
        _window->setWindowTitle( value["title"].get<std::string>() );
      }
    #endif

    bool setSize = false;
    bool setPosition = false;


    if ( value.count("width")
      && value["width"].is_number()
      && value["width"].get<int>()
    ) {
      setSize = true;
      width = value["width"].get<int>();
    }

    if ( value.count("height")
      && value["height"].is_number()
      && value["height"].get<int>()
    ) {
      setSize = true;
      height = value["height"].get<int>();
    }

    if ( value.count("x")
      && value["x"].is_number()
    ) {
      setPosition = true;
      position.x = value["x"].get<int>();
    }

    if ( value.count("y")
      && value["y"].is_number()
    ) {
      setPosition = true;
      position.y = value["y"].get<int>();
    }

    if ( setSize ) {
      _window->setWindowShape( width, height );
    }

    if ( setPosition ) {
      _window->setWindowPosition( position.x, position.y );
    }
  };

  void readLocal( ofJson & value );


  void addSubControls() {};

protected:
  ofAppBaseWindow * _window;
  ofPoint _position;

  void sizeFromWindow();
  void sizeToWindow();

};
