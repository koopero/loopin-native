#pragma once

#include "./Control.hpp"
#include "ofxLoopinFrame.h"

namespace ofxLoopin { namespace control {
class Numeric : public Control {
public:

  void setTarget( bool   * target );
  void setTarget( int    * target );
  void setTarget( float  * target );
  void setTarget( double * target );

  /*
   * Sets the value of the property, and ceases all tweening and other
   * effects.
   * @param value The new value.
   */
  void setValueHard( double _value ) {
    value = _value;
    stopAll();
  }

  /*
   * Gets the current value of the property as an integer.
   */
  int getValueInt() {
    return value;
  };
  float getValueFloat() {
    return value;
  };

  /*
   * Stop all effects, including noise, oscillator & tweening.
   */
  void stopAll () {
    // Nothing to stop yet
  };

protected:

  double  value         = 0.0;

  double  clock         = 0.0;

  float   oscLength     = 0.0;
  float   oscAmount     = 0.0;
  float   oscPhase      = 0.0;

  bool    * targ_bool   = NULL;
  float   * targ_float  = NULL;
  double  * targ_double = NULL;
  int     * targ_int    = NULL;


  void patchLocal( const ofJson & jsonValue ) {
    if ( jsonValue.is_number() ) {
      value = jsonValue;
    }
  };

  void readLocal( ofJson & jsonValue ) {
    jsonValue = value;
  };


private:
  float   oscValue();
};
}};