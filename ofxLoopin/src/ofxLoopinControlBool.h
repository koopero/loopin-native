#pragma once

#include "ofxLoopinControl.h"
#include "util/ofxLoopinJSON.hpp"

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

  void patchLocal( const ofJson & jsonValue ) {
    value = ofxLoopinJSONToBool( jsonValue );
  };

  void readLocal( ofJson & jsonValue ) {
    jsonValue = ofJson( value );
  };
};
