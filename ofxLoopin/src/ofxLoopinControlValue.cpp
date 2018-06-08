#include "ofxLoopinControlValue.h"

void ofxLoopinControlValue::patchLocal( const ofJson & val ) {
  if ( targ_int ) {
    if ( val.is_number() ) {
      // There were traces here for a reason, but I don't remember what it was.
      // cout << "targ_int " << val.get<int>() << endl;
      // cout << "targ_int_targ " << (uint64_t) targ_int  << endl;
      *targ_int = val.get<int>();
    } else if ( val.is_boolean() ) {
      *targ_int = val.get<bool>() ? 1 : 0;
    }
  }

  if ( targ_bool ) {
    if ( val.is_number() ) {
      *targ_bool = val.get<float>() != 0;
    } else if ( val.get<bool>() ) {
      *targ_bool = val.get<bool>();
    }
  }

  // ofxLoopinEvent event;
  // event.type = "VALUEPATH";
  // dispatch( event );

  if ( targ_string ) {
    if ( val.is_string() ) {
      *targ_string = val.get<std::string>();
    }
  }
}

void ofxLoopinControlValue::readLocal( ofJson & value ) {
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
