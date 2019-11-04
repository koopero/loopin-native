#pragma once

#include "./Control.hpp"
#include "../util/ofxLoopinJSON.hpp"

namespace ofxLoopin { namespace control {
class Bool : public Control {
public:
  Bool( bool value ) : value( value ) {};
  Bool() {};

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
}};