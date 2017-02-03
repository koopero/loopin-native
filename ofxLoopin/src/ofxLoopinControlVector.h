#pragma once

#include "ofxLoopinControl.h"
#include "ofxLoopinFrame.h"

template <LENGTH>
class ofxLoopinControlVector : public ofxLoopinControl {
public:
  static ofxLoopinControlVector VEC4( ofVec4f init ) {

  };

  static ofxLoopinControlVector VEC4( ofVec4f init ) {

  };

  ofxLoopinControlVector() {};

  operator ofVec4f() const { return value; };
  double operator()() const { return value; };

  /*
   * Gets the current value of the property as an integer.
   */
  int getValueInt() {
    return value;
  };
  float getValueFloat() {
    return value;
  };

protected:

  void updateLocal() {};

  double  value         = 0.0;

  void patchLocal( const Json::Value & jsonValue ) {
    if ( jsonValue.isNumeric() ) {
      value = jsonValue.asDouble();
    }
  };

  void readLocal( Json::Value & jsonValue ) {
    jsonValue = value;
  };
};
