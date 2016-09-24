#include "ofxLoopinControlNumeric.h"

void ofxLoopinControlNumeric::setTarget( bool   * target ) {
  targ_bool = target;
}

void ofxLoopinControlNumeric::setTarget( int    * target ) {
  targ_int = target;
}

void ofxLoopinControlNumeric::setTarget( float  * target ) {
  targ_float = target;
}

void ofxLoopinControlNumeric::setTarget( double * target ) {
  targ_double = target;
}

float ofxLoopinControlNumeric::oscValue () {
  // if ( !oscAmount )
  //   return 0.0;
  //
  // switch ( oscType ) {
  //
  //
  //   default:
  //   case SINE:
  //     osc = sin( phase * PI );
  //   break;
  // }

}
