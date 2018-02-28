#pragma once
#include "ofxJSON.h"

/**
  Wrapper for Json::Value.asBool(), with more javascript-style conversion
  from object, array and string.
*/
bool ofxLoopinJSONToBool( const Json::Value & value );

/**
  Same deal, but take a memebr key
*/
bool ofxLoopinJSONToBool( const Json::Value & value, const string & key );
