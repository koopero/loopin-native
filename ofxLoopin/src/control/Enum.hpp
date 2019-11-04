#pragma once

#include "./Control.hpp"

namespace ofxLoopin { namespace control {

template <class TYPE, TYPE DEFAULT>
class Enum : public ofxLoopin::control::Control {
public:

  bool enumKeyFromValue();

  Enum<TYPE,DEFAULT>() { enumAddOptions(); };
  // Enum<TYPE,DEFAULT>( TYPE value ) : _value( value ) { enumKeyFromValue(); };
  TYPE operator()() const { return _value; };
  operator TYPE() const { return _value; };
  void operator= ( const TYPE & value ) { _value = value; }

  TYPE getEnumValue() const { return _value; };

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
    // key = enumMungeString( key );
    // _enumMapMunge[key] = value;
  }

  void enumAddOptionBool( bool key, TYPE value ) {
    _enumMapBool[key] = value;
  }

  void enumAddOptionBool( bool key, string ref ) {
    _enumMapBool[key] = _enumMap[ref];
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

  void patchLocal ( const ofJson & val ) {
    if ( val.is_boolean() ) {
      patchBool( val.get<bool>() );
    }
  }

  void patchBool( bool value ) {
    if ( _enumMapBool.count( value ) ) {
      _value = _enumMapBool[value];
    }
  }

  void readLocal( ofJson & value ) {
    value = _key;
  };

  string enumMungeString ( const string & str );

  string _key;
  TYPE _value = DEFAULT;
  std::map<string,TYPE> _enumMap;
  std::map<bool,TYPE> _enumMapBool;
  std::map<string,TYPE> _enumMapMunge;

  void addSubControls() {
    enumAddOptions();
  };

  virtual void enumAddOptions() {};
}; } }
