#pragma once

#include "ofxLoopinControl.h"

template <int LENGTH>
class ofxLoopinControlVector : public ofxLoopinControl {
public:
  ofxLoopinControlVector() {};
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

  void setAxis( int axis, const Json::Value & val ) {
    if ( axis >= 0 && axis < LENGTH ) {
      component[axis].patch( val );
    }
  }

protected:
  void updateLocal() {};

  void patchLocal( const Json::Value & val ) {
    if ( val.isNumeric() ) {
      for ( int axis = 0; axis < LENGTH && axis < 3; axis ++ )
        setAxis( axis, val );
    }

    if ( val.isArray() ) {
      for ( int valIndex = 0; valIndex < val.size(); valIndex ++ ) {
        setAxis( valIndex, val[ valIndex ]);
      }
    }

    if ( val.isObject() ) {
      for( Json::ValueIterator it = val.begin(); it != val.end() ; it++) {
        int axis = keyToAxis( it.key().asString() );
        setAxis( axis, (*it) );
      }
    }
  };

  int keyToAxis( const string & key ) {
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

  void readLocal( Json::Value & jsonValue ) {
    jsonValue = Json::Value( Json::ValueType::arrayValue );
    for ( int axis = 0; axis < LENGTH; axis++ )
      jsonValue[axis] = getAxis( axis );
  };
};
