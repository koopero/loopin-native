#include "ofxLoopinControlValue.h"

void ofxLoopinControlValue::patchLocal( const Json::Value & val ) {
  if ( targ_int ) {
    if ( val.isNumeric() ) {
      // There were traces here for a reason, but I don't remember what it was.
      // cout << "targ_int " << val.asInt64() << endl;
      // cout << "targ_int_targ " << (uint64_t) targ_int  << endl;
      *targ_int = val.asInt64();
    } else if ( val.isBool() ) {
      *targ_int = val.asBool() ? 1 : 0;
    }
  }

  if ( targ_bool ) {
    if ( val.isNumeric() ) {
      *targ_bool = val.asFloat() != 0;
    } else if ( val.isBool() ) {
      *targ_bool = val.asBool();
    }
  }

  // ofxLoopinEvent event;
  // event.type = "VALUEPATH";
  // dispatch( event );

  if ( targ_string ) {
    if ( val.isString() ) {
      *targ_string = val.asString();
    }
  }
}

void ofxLoopinControlValue::readLocal( Json::Value & value ) {
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
