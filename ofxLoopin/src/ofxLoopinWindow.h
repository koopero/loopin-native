#pragma once

#include "ofAppBaseWindow.h"

#include "ofxLoopinControl.h"

class ofxLoopinWindow : public ofxLoopinControl {
public:
  int width = 0;
  int height = 0;

  void setAppBaseWindow( ofAppBaseWindow * window );

protected:
  void patchKey( string key, const Json::Value & val ) {};
  void patchLocal( const Json::Value & value ) {

    ofxLoopinEvent event = ofxLoopinEvent("debug");

    event.data["_window"] = 3;


    if ( !value.isObject() )
      return;

    if ( !_window )
      return;

    if ( value.isMember("fullscreen") ) {
      _window->setFullscreen( value["fullscreen"].asBool() );
    }

    if ( value.isMember("title")
      && value["title"].isString()
    ) {
      _window->setWindowTitle( value["title"].asString() );
    }

    bool setSize = false;

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

    if ( setSize ) {
      _window->setWindowShape( width, height );
    }
  };

  void readLocal( Json::Value & value );

  void addSubControls() {};

protected:
  ofAppBaseWindow * _window;

  void sizeFromWindow();
};
