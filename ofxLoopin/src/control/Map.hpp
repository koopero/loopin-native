#pragma once

#include "./control/Control.hpp"

namespace ofxLoopin { namespace control {
template <class child_type>
class Map : public Control {
public:
  string defaultKey = "";

  child_type * getByKey( string key, bool create = false );

  string randomKey() {
    if ( !_map.size() )
      return "";

    auto it = _map.begin();
    std::advance(it, rand() % _map.size());

    return it->first;
  }

  std::map<string, child_type> & getMap() {
    return _map;
  }

  void update() {
    for( auto it = _map.begin(); it != _map.end(); it++) {
      Control &item = it->second;
      item.update();
    }
  };


protected:
  void patchKey( string key, const ofJson & val );
  std::map<string, child_type> _map;

  void createKey( string key ) {
    // _map[key] = child_type();
    // _map.emplace( key );
    _map[key].path = path + "/" + key;
    _map[key].root = root;
    _map[key].key = key;

    _map[key].setupControl();

    addSubControl( key, &_map[key] );
  }


};


template <class child_type>
child_type * Map<child_type>::getByKey( string key, bool create ) {

  if ( !key.size() ) {
    if ( defaultKey.size() )
      key = defaultKey;
    else
      // If you're looking for jankiness, it's here.
      key = randomKey();
  }

  if ( !_map.count( key ) ) {
    if ( !create ) {
      return NULL;
    }

    createKey( key );
  }

  return &_map[key];
}

template <class child_type>
void Map<child_type>::patchKey( string key, const ofJson & val ) {
  bool hasVal = !val.is_null();
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
};
}};
