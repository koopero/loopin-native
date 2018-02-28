#pragma once

#include "ofMain.h"

#include "ofxLoopinControl.h"
#include "ofxLoopinHasInfo.h"

#include "util/json.hpp"


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

  Json::Value infoGet();

protected:
  void patchKey( string key, const Json::Value & val ) {};
  void patchLocal( const Json::Value & value ) {

    ofxLoopinEvent event = ofxLoopinEvent("debug");

    event.data["_window"] = 3;

    ofPoint position = _window->getWindowPosition();

    if ( !value.isObject() )
      return;

    if ( !_window )
      return;

    if ( value.isMember("fullscreen") ) {
      _window->setFullscreen( ofxLoopinJSONToBool( value["fullscreen"] ) );
    }

    if ( value.isMember("title")
      && value["title"].isString()
    ) {
      _window->setWindowTitle( value["title"].asString() );
    }

    bool setSize = false;
    bool setPosition = false;


    if ( value.isMember("width")
      && value["width"].isNumeric()
      && value["width"].asInt()
    ) {
      setSize = true;
      width = value["width"].asInt();
    }

    if ( value.isMember("height")
      && value["height"].isNumeric()
      && value["height"].asInt()
    ) {
      setSize = true;
      height = value["height"].asInt();
    }

    if ( value.isMember("x")
      && value["x"].isNumeric()
    ) {
      setPosition = true;
      position.x = value["x"].asInt();
    }

    if ( value.isMember("y")
      && value["y"].isNumeric()
    ) {
      setPosition = true;
      position.y = value["y"].asInt();
    }

    if ( setSize ) {
      _window->setWindowShape( width, height );
    }

    if ( setPosition ) {
      _window->setWindowPosition( position.x, position.y );
    }
  };

  void readLocal( Json::Value & value );


  void addSubControls() {};

protected:
  ofAppBaseWindow * _window;
  ofPoint _position;

  void sizeFromWindow();
  void sizeToWindow();

};
