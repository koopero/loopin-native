#pragma once

#include "ofxJSON.h"

#include <string>

using std::string;

class ofxLoopinEvent {
public:
  static const string Loaded;

  ofxLoopinEvent() {};
  ofxLoopinEvent( string type ) : type( type ) {};


  string type;
  string path;
  Json::Value data = Json::objectValue;

  static ofxLoopinEvent fileNotFound( const string & file );

};
