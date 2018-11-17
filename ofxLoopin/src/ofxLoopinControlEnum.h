#pragma once

#include "ofxLoopinControl.h"

template <class E, E DEFAULT>
class ofxLoopinControlEnum : public ofxLoopinControl {
public:

  string getKey() const {
    return _key;
  }

  void setKey( const string & key ) {
    if ( _keyToEnum.count( key ) ) {
      _key = key;
      _value = _keyToEnum[key];
    }
  }

  void setEnumValue( E value ) {
    for ( auto it : _keyToEnum ) {
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

    _keyToEnum[key] = value;
  }

  void setKeyBool( bool boo, string key ) {
    _boolToKey[boo] = key;
  }

  E getEnumValue() const {
    return _value;
  }

protected:
  void patchString( string value ) {
    if ( _keyToEnum.count( value ) ) {
      _key = value;
      _value = _keyToEnum[value];
    }
  };

  void patchLocal( const ofJson & value ) {
    if ( value.is_boolean() ) {
      bool valueB = value;
      if ( _boolToKey.count( valueB ) ) {
        _key = _boolToKey[valueB];
        _value = _keyToEnum[_key];
      }
    }
  }

  void readLocal( ofJson & value ) {
    value = _key;
  };


private:
  string _key;
  E _value = DEFAULT;
  std::map<string,E> _keyToEnum;
  std::map<bool,string>   _boolToKey;
};
