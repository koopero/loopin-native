#pragma once

#include "./Control.hpp"

namespace ofxLoopin { namespace control {
class Value : public Control {
public:
  Value() {};
  Value( string * target ) : targ_string( target ) {} ;
  Value( int * target ) : targ_int( target ) {} ;
  Value( bool * target ) : targ_bool( target ) {} ;

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
}};