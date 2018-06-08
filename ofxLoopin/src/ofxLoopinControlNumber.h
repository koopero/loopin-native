#pragma once

#include "ofxLoopinControl.h"
#include "ofxLoopinFrame.h"

class ofxLoopinControlNumber : public ofxLoopinControl {
public:
  ofxLoopinControlNumber( double value ) : value( value ) {};
  ofxLoopinControlNumber( int _value ) : value( _value ) {};
  ofxLoopinControlNumber() {};


  double operator()() const { return value; };
  operator double() const { return value; };

  /*
   * Gets the current value of the property as an integer.
   */
  int getValueInt() {
    return value;
  };
  float getValueFloat() {
    return value;
  };

  void setValue( double v ) { value = v; };

protected:

  void updateLocal() {};

  double  value         = 0.0;

  void patchLocal( const ofJson & jsonValue ) {
    if ( jsonValue.is_number() ) {
      value = jsonValue;
    }
  };

  void readLocal( ofJson & jsonValue ) {
    jsonValue = value;
  };
};


class ofxLoopinControlInt : public ofxLoopinControl {
public:
  ofxLoopinControlInt( int _value ) : value( _value ) {};
  ofxLoopinControlInt() {};

  int operator()() const { return (int) value; };
  operator int() const { return (int) value; };

  int getValueInt() {
    return value;
  };

protected:
  void updateLocal() {};

  int value         = 0;

  void patchLocal( const ofJson & jsonValue ) {
    if ( jsonValue.is_number() ) {
      value = jsonValue;
    }

    if ( jsonValue.is_string() ) {
      // Try to parse anyway.
      std::stringstream ss;
      ss << jsonValue.get<std::string>();
      ss >> value;
    }
  };

  void readLocal( ofJson & jsonValue ) {
    jsonValue = value;
  };
};
