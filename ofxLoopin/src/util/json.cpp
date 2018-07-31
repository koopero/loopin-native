#include "json.hpp"

/**
  Wrapper for Json::Value.asBool(), with more javascript-style conversion
  from object, array and string.
*/
bool ofxLoopinJSONToBool( const Json::Value & value ) {
  if ( value.isString() )
    return !value.asString().empty();

  if ( value.isObject() || value.isArray() )
    return true;

  return value.asBool();
};

/**
  Same deal, but take a memebr key
*/

bool ofxLoopinJSONToBool( const Json::Value & value, const std::string & key ) {
  if ( !value.isObject() || !value.isMember( key ) )
    return false;

  return ofxLoopinJSONToBool( value );
};
