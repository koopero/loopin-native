#pragma once

#include "../ofxLoopinControl.h"

namespace ofxLoopin { namespace type {

template <class TYPE, TYPE DEFAULT>
class Enum : public ofxLoopinControl {
public:

  bool enumKeyFromValue();

  Enum<TYPE,DEFAULT>() {};
  Enum<TYPE,DEFAULT>( TYPE value ) : _value( value ) { enumKeyFromValue(); };
  TYPE operator()() const { return _value; };
  operator TYPE() const { return _value; };
  void operator= ( const TYPE & value ) { _value = value; }


  string getKey() const {
    return _key;
  }

  void setKey( const string & key ) {
    if ( _enumMap.count( key ) ) {
      _key = key;
      _value = _enumMap[key];
    }
  }

  void setEnumValue( TYPE value ) {
    for ( auto it : _enumMap ) {
      if ( value == it.second ) {
        _value = value;
        _key = it.first;
        return;
      }
    }
  }


  void enumAddOption( string key, TYPE value ) {
    // Set the default value first.
    if ( !_key.size() )
      _key = key;

    _enumMap[key] = value;
    key = enumMungeString( key );
    _enumMungeMap[key] = value;
  }

  TYPE enumGetValue() const {
    return _value;
  }

protected:
  void patchString( string value ) {
    if ( _enumMap.count( value ) ) {
      _key = value;
      _value = _enumMap[value];
    }
  };

  void readLocal( ofJson & value ) {
    value = _key;
  };

  string enumMungeString ( const string & str );

  string _key;
  TYPE _value = DEFAULT;
  map<string,TYPE> _enumMap;
  map<string,TYPE> _enumMungeMap;

}; } }
