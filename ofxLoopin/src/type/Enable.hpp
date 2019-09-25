#pragma once

#include "./Enum.hpp"

namespace ofxLoopin { namespace type {

enum EnableValues {
  ENABLE_NO,
  ENABLE_YES,
  ENABLE_ONCE
};

class Enable : public Enum<EnableValues,ENABLE_YES> {
public:
  Enable() {
    enumAddOption("yes", ENABLE_YES );
    enumAddOption("no", ENABLE_NO );
    enumAddOption("once", ENABLE_ONCE );

    enumAddOptionBool( false, ENABLE_NO );
    enumAddOptionBool( true, ENABLE_YES );

  };

  bool isEnabledOnce() {
    if ( _value == ENABLE_YES )
      return true; 

    if ( _value == ENABLE_ONCE ) {
      resetOnce();
      return true;
    }

    return false;
  }  

  bool isEnabled() {
    // Promise to call resetOnce()! 
    return _value == ENABLE_YES || _value == ENABLE_ONCE;
  }

  void resetOnce() {
    ofxLoopinEvent event;
    event.type = "done";
    dispatch( event );
    _value = ENABLE_NO;
  }
};
}};