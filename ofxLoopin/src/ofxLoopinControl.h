#pragma once

#include "ofxJSON.h"

#include "ofxLoopinEvent.h"

#include <iostream>

class ofxLoopinRoot;
class ofxLoopinControl {
public:

  ~ofxLoopinControl() {

  };

  void patch( const Json::Value & val );

  virtual void update();

  virtual void dispatch( string type ) {
    ofxLoopinEvent event;
    event.type = type;
    dispatch( event );
  };
  virtual void dispatch( ofxLoopinEvent & event );

  string path;
  string key;

  ofxLoopinRoot * root = NULL;

  Json::Value read();

  ofxLoopinControl * walk ( const string & path );

  void readToValue( Json::Value & value );


protected:

  virtual void updateLocal() {};
  virtual void patchKey( string key, const Json::Value & val ) {};
  virtual void patchSubs( const Json::Value & value ) {};
  virtual void patchLocal( const Json::Value & value ) {};
  virtual void patchLocalAfter( const Json::Value & value ) {};
  virtual void patchString( const string & value ) {};

  virtual void readLocal( Json::Value & value ) {};
  virtual void readSubs( Json::Value & value );

  void addSubControl( ofxLoopinControl * control );
  void addSubControl( string key, ofxLoopinControl * control );

  virtual void addSubControls() {};

private:

  vector <ofxLoopinControl *> subsUnkeyed;
  map< string, ofxLoopinControl *> subs;


public:
  void setupControl() {
    addSubControls();
  };

};
