#pragma once

#include "./Control.hpp"
#include "../clock/Frame.hpp"

namespace ofxLoopin { namespace control {
class Number : public Control {
public:
  Number( double value ) : value( value ) {};
  Number( int _value ) : value( _value ) {};
  Number() {};


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


class Int : public Control {
public:
  Int( int _value ) : value( _value ) {};
  Int() {};

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
      value = jsonValue.get<double>();
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
}};