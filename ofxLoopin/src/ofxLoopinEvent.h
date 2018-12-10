#pragma once

#include <string>
#include "ofJson.h"

using std::string;

class ofxLoopinEvent {
public:
  static const string Loaded;

  ofxLoopinEvent() {};
  ofxLoopinEvent( string type ) : type( type ) {};


  string type;
  string path;
  ofJson data = ofJson::object();

  static ofxLoopinEvent fileNotFound( const string & file );

};
