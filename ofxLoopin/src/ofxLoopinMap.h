#pragma once

#include "ofxLoopinControl.h"

template <class child_type>
class ofxLoopinMap : public ofxLoopinControl {
public:
  void patchKey( string key, const Json::Value &val );

  string defaultKey;

  child_type * getByKey( string key, bool create = false );

  string randomKey() const {
    if ( !_map.size() )
      return "";

    auto it = _map.begin();
    std::advance(it, rand() % _map.size());

    return it->first;
  }

  map<string, child_type> & getMap() {
    return _map;
  }

  void update() {
    for( auto it = _map.begin(); it != _map.end(); it++) {
      ofxLoopinControl &item = it->second;
      item.update();
    }
  };


protected:
  void patchChildren( const Json::Value & value );

  map<string, child_type> _map;

  void createKey( string key ) {
    _map[key] = child_type();
    _map[key].path = path + "/" + key;
    _map[key].root = root;
    _map[key].key = key;

    _map[key].setupControl();

    addSubControl( key, &_map[key] );
  }


};


template <class child_type>
child_type * ofxLoopinMap<child_type>::getByKey( string key, bool create ) {

  if ( !key.size() ) {
    if ( defaultKey.size() )
      key = defaultKey;
    else
      // If you're looking for jankiness, it's here.
      key = randomKey();
  }

  if ( !_map.count( key ) ) {
    if ( !create ) {
      cerr << "keyNotFound! (" << key << ")" << endl;
      return NULL;
    }

    createKey( key );
  }

  return &_map[key];
}

template <class child_type>
void ofxLoopinMap<child_type>::patchChildren( const Json::Value & value ) {
}

template <class child_type>
void ofxLoopinMap<child_type>::patchKey( string key, const Json::Value &val ) {

  bool hasVal = !val.isNull();
  child_type * item = _map.count( key ) ? &_map[key] : NULL;


  if ( hasVal && !item ) {
    // create
    createKey(key);
    item = &_map[key];
  } else if ( !hasVal && item ) {
    // delete
  }

  if ( item ) {
    // patch
    item->patch( val );
  }



}
