#pragma once

#include "ofxLoopinControl.h"

namespace ofxLoopin { namespace type {

template <int LENGTH>
class Vector : public ofxLoopinControl {
public:
  Vector() {};
  ofxLoopinControlNumber component[LENGTH];

  float getAxis( int axis = 0, float defaultValue = 0.0 ) {
    if ( axis < 0 || axis > LENGTH )
      return defaultValue;

    return component[axis].getValueFloat();
  };

  ofVec3f getValueVec2() {
    return ofVec2f( getAxis(0), getAxis(1) );
  };

  ofVec3f getValueVec3() {
    return ofVec3f( getAxis(0), getAxis(1), getAxis(2) );
  };

  ofVec4f getValueVec4() {
    return ofVec4f( getAxis(0), getAxis(1), getAxis(2), getAxis(3) );
  };


  void setAxis( int axis, float value ) {
    if ( axis >= 0 && axis < LENGTH ) {
      component[axis].setValue( value );
    }
  }

  void setAxis( int axis, ofJson & val ) {
    if ( axis >= 0 && axis < LENGTH ) {
      component[axis].patch( val );
    }
  }

protected:
  void updateLocal() {};

  void patchLocal( const ofJson & val ) {
    if ( val.is_number() ) {
      for ( unsigned int axis = 0; axis < LENGTH && axis < 3; axis ++ )
        setAxis( axis, val );
    }

    if ( val.is_array() ) {
      for ( unsigned int valIndex = 0; valIndex < val.size(); valIndex ++ ) {
        setAxis( valIndex, val[ valIndex ]);
      }
    }

    if ( val.is_object() ) {
      for( auto it = val.begin(); it != val.end() ; it++) {
        // unsigned int axis = keyToAxis( it.key() );
        // setAxis( axis, (*it) );
      }
    }
  };

  virtual int keyToAxis( const string & key ) {
    if ( key == "x" || key == "0" ) return 0;
    if ( key == "y" || key == "1" ) return 1;
    if ( key == "z" || key == "2" ) return 2;
    if ( key == "w" || key == "3" ) return 3;

    if ( key == "r" || key == "red" ) return 0;
    if ( key == "g" || key == "green" ) return 1;
    if ( key == "b" || key == "blue" ) return 2;
    if ( key == "a" || key == "alpha" ) return 3;

    return -1;
  }

  void readLocal( ofJson & jsonValue ) {
    jsonValue = ofJson::array();
    for ( int axis = 0; axis < LENGTH; axis++ )
      jsonValue[axis] = getAxis( axis );
  };
};
}}
