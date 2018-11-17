#pragma once

#include "ofxLoopinControl.h"

class ofxLoopinControlValue : public ofxLoopinControl {
public:
  ofxLoopinControlValue() {};
  ofxLoopinControlValue( string * target ) : targ_string( target ) {} ;
  ofxLoopinControlValue( int * target ) : targ_int( target ) {} ;
  ofxLoopinControlValue( bool * target ) : targ_bool( target ) {} ;

  ofJson value;

  int getValueInt() {
    return value.get<int>();
  };

protected:
  void patchLocal( const ofJson & value );

  void readLocal( ofJson & value );


private:
  bool    * targ_bool   = nullptr;
  float   * targ_float  = nullptr;
  double  * targ_double = nullptr;
  int     * targ_int    = nullptr;
  string  * targ_string = nullptr;
};
