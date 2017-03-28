#pragma once

#include "ofxLoopinControl.h"

class ofxLoopinControlBool : public ofxLoopinControl {
public:
  ofxLoopinControlBool( bool value ) : value( value ) {};
  ofxLoopinControlBool() {};

  operator bool() const { return value; };

  /*
   * Gets the current value of the property as an integer.
   */
  bool getValue() {
    return value;
  };


protected:

  void updateLocal() {};

  bool  value         = false;

  void patchLocal( const Json::Value & jsonValue ) {
    if ( jsonValue.isNumeric()  ) {
      value = jsonValue.asFloat() != 0 && !isnan( jsonValue.asFloat() );
    } else {
      value = jsonValue.asBool();
    }
  };

  void readLocal( Json::Value & jsonValue ) {
    jsonValue = Json::Value( value );
  };
};
