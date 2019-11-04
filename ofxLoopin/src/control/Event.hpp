#pragma once

#include <string>
#include "ofJson.h"

using std::string;

namespace ofxLoopin { namespace control {
class Event {
public:
  static const string Loaded;

  Event() {};
  Event( string type ) : type( type ) {};

  string type;
  string path;
  ofJson data = ofJson::object();

  static Event fileNotFound( const string & file );
};
}};
