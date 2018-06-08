#pragma once

#include "ofJson.h"
#include "ofxLoopinEvent.h"

#include <iostream>

class ofxLoopinRoot;
class ofxLoopinControl {
public:

  ~ofxLoopinControl() {

  };

  void patch( const ofJson & val );

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

  ofJson read();

  ofxLoopinControl * walk ( const string & path );

  void readToValue( ofJson & value );

  std::map< string, ofxLoopinControl *> getSubs() { return subs; };

protected:

  virtual void updateLocal() {};
  virtual void patchKey( string key, const ofJson & val ) {};
  virtual void patchSubs( ofJson & value ) {};
  virtual void patchLocal( const ofJson & value ) {};
  virtual void patchLocalAfter( const ofJson & value ) {};
  virtual void patchString( string value ) {};

  virtual void readLocal( ofJson & value ) {};
  virtual void readSubs( ofJson & value );

  void addSubControl( ofxLoopinControl * control );
  void addSubControl( string key, ofxLoopinControl * control );

  virtual void addSubControls() {};

private:

  std::vector <ofxLoopinControl *> subsUnkeyed;
  std::map< string, ofxLoopinControl *> subs;


public:
  void setupControl() {
    addSubControls();
  };

};
