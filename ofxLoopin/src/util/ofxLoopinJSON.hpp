#pragma once
#include "ofJson.h"

/**
  Wrapper for ofJson.as_boolean(), with more javascript-style conversion
  from object, array and string.
*/
bool ofxLoopinJSONToBool( const ofJson & value );

/**
  Same deal, but take a memebr key
*/
bool ofxLoopinJSONToBool( const ofJson & value, const std::string & key );
