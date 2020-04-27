#pragma once

#include "./Enum.hpp"

namespace ofxLoopin { namespace control {

enum EnableValues {
  ENABLE_NO,
  ENABLE_YES,
  ENABLE_ONCE,
  ENABLE_AUTO
};

class Enable : public Enum<EnableValues,ENABLE_YES> {
public:
  Enable() {
    enumAddOption("yes", ENABLE_YES );
    enumAddOption("true", ENABLE_YES );
    enumAddOption("no", ENABLE_NO );
    enumAddOption("false", ENABLE_NO );
    enumAddOption("auto", ENABLE_AUTO );
    enumAddOption("once", ENABLE_ONCE );

    enumAddOptionBool( false, ENABLE_NO );
    enumAddOptionBool( true, ENABLE_YES );
  };

  bool isEnabledOnce( bool automatic = false ) {
    if ( _value == ENABLE_YES )
      return true; 

    if ( _value == ENABLE_AUTO )
      return automatic;

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
    if ( _value == ENABLE_ONCE ) {
      ofxLoopin::control::Event event;
      event.type = "done";
      dispatch( event );
      _value = ENABLE_NO;
    }
  }
};
}};