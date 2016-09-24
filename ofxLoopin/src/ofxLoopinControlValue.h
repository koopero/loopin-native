#pragma once

#include "ofxLoopinControl.h"

class ofxLoopinControlValue : public ofxLoopinControl {
public:
  ofxLoopinControlValue() {};
  ofxLoopinControlValue( string * target ) : targ_string( target ) {} ;
  ofxLoopinControlValue( int * target ) : targ_int( target ) {} ;
  ofxLoopinControlValue( bool * target ) : targ_bool( target ) {} ;

  Json::Value value;

  int getValueInt() {
    return value.asInt();
  };

protected:
  void patchLocal( const Json::Value & value );

  void readLocal( Json::Value & value );


private:
  bool    * targ_bool   = nullptr;
  float   * targ_float  = nullptr;
  double  * targ_double = nullptr;
  int     * targ_int    = nullptr;
  string  * targ_string = nullptr;
};
