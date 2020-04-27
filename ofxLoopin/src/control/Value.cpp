#include "./Value.hpp"

void ofxLoopin::control::Value::patchLocal( const ofJson & val ) {
  if ( targ_int ) {
    if ( val.is_number() ) {
      *targ_int = val.get<int>();
    } else if ( val.is_boolean() ) {
      *targ_int = val.get<bool>() ? 1 : 0;
    }
  }

  if ( targ_bool ) {
    if ( val.is_number() ) {
      *targ_bool = val.get<float>() != 0;
    } else if ( val.is_boolean() ) {
      *targ_bool = val.get<bool>();
    }
  }

  if ( targ_string ) {
    if ( val.is_string() ) {
      *targ_string = val.get<std::string>();
    }
  }
}

void ofxLoopin::control::Value::readLocal( ofJson & value ) {
  if ( targ_string ) {
    value = *targ_string;
  }

  if ( targ_int ) {
    value = *targ_int;
  }

  if ( targ_bool ) {
    value = *targ_bool;
  }
}
