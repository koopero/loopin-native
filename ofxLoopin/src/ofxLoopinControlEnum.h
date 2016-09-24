#pragma once

#include "ofxLoopinControl.h"

template <class E, E DEFAULT>
class ofxLoopinControlEnum : public ofxLoopinControl {
public:

  string getKey() const {
    return _key;
  }

  void setKey( const string & key ) {
    if ( _map.count( key ) ) {
      _key = key;
      _value = _map[key];
    }
  }

  void setEnumValue( E value ) {
    for ( auto it : _map ) {
      if ( value == it.second ) {
        _value = value;
        _key = it.first;
        return;
      }
    }
  }


  void setEnumKey( const string & key, E value ) {
    // Set the default value first.
    if ( !_key.size() )
      _key = key;

    _map[key] = value;
  }

  E getEnumValue() const {
    return _value;
  }

protected:
  void patchString( const string & value ) {
    if ( _map.count( value ) ) {
      _key = value;
      _value = _map[value];
    }
  };

  void readLocal( Json::Value & value ) {
    value = _key;
  };


private:
  string _key;
  E _value = DEFAULT;
  map<string,E> _map;
};
