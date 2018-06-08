#include "ofxLoopinJSON.hpp"

/**
  Wrapper for ofJson.as_boolean(), with more javascript-style conversion
  from object, array and string.
*/
bool ofxLoopinJSONToBool( const ofJson & value ) {
  if ( value.is_string() )
    return !value.get<std::string>().empty();

  if ( value.is_object() || value.is_array() )
    return true;

  return value;
};

/**
  Same deal, but take a memebr key
*/

bool ofxLoopinJSONToBool( const ofJson & value, const std::string & key ) {
  if ( !value.is_object() || !value.count( key ) )
    return false;

  return ofxLoopinJSONToBool( value );
};
