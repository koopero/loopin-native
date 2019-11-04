#pragma once

#include "ofJson.h"
#include "ofxLoopinEvent.h"

#include <iostream>

class ofxLoopinRoot;

namespace ofxLoopin { namespace control {
class Control {
public:

  ~Control() {

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

  Control * walk ( const string & path );

  void readToValue( ofJson & value );

  std::map< string, Control *> getSubs() { return subs; };

protected:

  virtual void updateLocal() {};
  virtual void patchKey( string key, const ofJson & val );
  virtual void patchSubs( ofJson & value ) {};
  virtual void patchLocal( const ofJson & value ) {};
  virtual void patchLocalAfter( const ofJson & value ) {};
  virtual void patchString( string value ) {};

  virtual void readLocal( ofJson & value ) {};
  virtual void readSubs( ofJson & value );

  void addSubControl( Control * control );
  void addSubControl( string key, Control * control );

  virtual void addSubControls() {};

private:

  std::vector <Control *> subsUnkeyed;
  std::map< string, Control *> subs;


public:
  void setupControl() {
    addSubControls();
  };

};
}};
