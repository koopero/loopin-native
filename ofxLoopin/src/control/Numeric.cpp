#include "./Numeric.hpp"

void ofxLoopin::control::Numeric::setTarget( bool   * target ) {
  targ_bool = target;
}

void ofxLoopin::control::Numeric::setTarget( int    * target ) {
  targ_int = target;
}

void ofxLoopin::control::Numeric::setTarget( float  * target ) {
  targ_float = target;
}

void ofxLoopin::control::Numeric::setTarget( double * target ) {
  targ_double = target;
}

float ofxLoopin::control::Numeric::oscValue () {
  // Future proof :P
  return 0;
}
