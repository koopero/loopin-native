#pragma once

#include "./control/Map.hpp"
#include "../base/Root.hpp"
#include <assert.h>

namespace ofxLoopin { namespace control {
template <class TYPE, class HAS>
class Reference : public Control {
public:
  string key;

  TYPE * getPointer( bool create = true ) {

    if ( root == nullptr ){
      ofxLoopin::control::Event event("rootFuckup");
      dispatch(event);
    };

    auto has = dynamic_cast<HAS *> ( root );

    if ( has == nullptr ) {
      ofxLoopin::control::Event event("hasFuckup");
      dispatch(event);
    }

    ofxLoopin::control::Map<TYPE> * map = has->__getMap();

    if ( map == nullptr ) {
      ofxLoopin::control::Event event("mapFuckup");
      dispatch(event);
    }

    return map->getByKey( key, create );
  };

  void next() {};
  void prev() {};


protected:
  void patchString( string value ) {
    key = value;
  }

  void readLocal( ofJson & value ) {
    if ( key.size() )
      value = key;
    else
      value = ofJson();
  }

private:

};
}};