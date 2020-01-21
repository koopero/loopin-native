#pragma once

#include "ofMain.h"
#include "./Control.hpp"
#include "./Number.hpp"

namespace ofxLoopin { namespace control {

template <int LENGTH>
class Vector : public Control {
public:
  Vector() {
    for ( int axis = 0; axis < LENGTH; axis ++ )
      component[axis] = 0.;
  };
  ofxLoopin::control::Number component[LENGTH];

  float getAxis( int axis = 0, float defaultValue = 0.0 ) {
    if ( axis < 0 || axis > LENGTH )
      return defaultValue;

    return component[axis].getValueFloat();
  };

  ofVec2f getValueVec2() {
    return ofVec2f( getAxis(0), getAxis(1) );
  };

  ofVec2f getXY() {
    return ofVec2f( getAxis(0), getAxis(1) );
  };

  ofVec2f getZW() {
    return ofVec2f( getAxis(2), getAxis(3) );
  };

  ofVec3f getValueVec3() {
    return ofVec3f( getAxis(0), getAxis(1), getAxis(2) );
  };

  ofVec4f getValueVec4() {
    return ofVec4f( getAxis(0), getAxis(1), getAxis(2), getAxis(3) );
  };

  ofMatrix4x4 getValueMat4() {
    float val[LENGTH];
    for ( int axis = 0; axis < LENGTH; axis ++ )
      val[axis] = component[axis].getValueFloat();  
    
    auto matrix = ofMatrix4x4( val );

    return matrix;
  };

  void setAxis( int axis, float value ) {
    if ( axis >= 0 && axis < LENGTH ) {
      if ( axis < 2 ) 
        positionIsSet = true;
      component[axis].setValue( value );
    }
  }

  void setXY( const ofVec2f & vec ) {
    setAxis( 0, vec.x );
    setAxis( 1, vec.y );
  }

  void setZW( const ofVec2f & vec ) {
    setAxis( 2, vec.x );
    setAxis( 3, vec.y );
  }

  void setAxis( int axis, ofJson & val ) {
    if ( axis >= 0 && axis < LENGTH ) {
      if ( axis < 2 ) 
        positionIsSet = true;
      component[axis].patch( val );
    }
  }

  bool positionIsSet = false;

protected:
  void updateLocal() {};

  void patchLocal( const ofJson & val ) {
    if ( val.is_number() ) {
      for ( unsigned int axis = 0; axis < LENGTH && axis < 3; axis ++ )
        setAxis( axis, val );
    }

    if ( val.is_array() ) {
      for ( unsigned int valIndex = 0; valIndex < val.size(); valIndex ++ ) {
        setAxis( valIndex, val[ valIndex ] );
      }
    } else if ( val.is_object() ) {
      ofJson ob = val;
      for( ofJson::iterator it = ob.begin(); it != ob.end() ; it++) {
        int axis = keyToAxis( it.key() );
        setAxis( axis, it.value() );
      }
    }
  };

  virtual int keyToAxis( const string & key ) {
    char *endptr;
    long value = strtol(key.c_str(), &endptr, 10);

    if ( endptr != key.c_str() )
    {
      return value;
    }

    if ( key == "x" ) return 0;
    if ( key == "y" ) return 1;
    if ( key == "z" ) return 2;
    if ( key == "w" ) return 3;

    if ( key == "r" || key == "red" ) return 0;
    if ( key == "g" || key == "green" ) return 1;
    if ( key == "b" || key == "blue" ) return 2;
    if ( key == "a" || key == "alpha" ) return 3;

    if ( key == "u" ) return 0;
    if ( key == "v" ) return 1;
    if ( key == "s" ) return 2;
    if ( key == "t" ) return 3;

    return -1;
  }

  void readLocal( ofJson & jsonValue ) {
    jsonValue = ofJson::array();
    for ( int axis = 0; axis < LENGTH; axis++ )
      jsonValue[axis] = getAxis( axis );
  };
};
}}
