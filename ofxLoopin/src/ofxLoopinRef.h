#pragma once

#include "ofxLoopinMap.h"
#include "ofxLoopinRoot.h"
#include <assert.h>

template <class TYPE, class HAS>
class ofxLoopinRef : public ofxLoopin::control::Control {
public:
  string key;

  TYPE * getPointer( bool create = true ) {

    if ( root == nullptr ){
      ofxLoopinEvent event("rootFuckup");
      dispatch(event);
    };

    auto has = dynamic_cast<HAS *> ( root );

    if ( has == nullptr ) {
      ofxLoopinEvent event("hasFuckup");
      dispatch(event);
    }

    ofxLoopinMap<TYPE> * map = has->__getMap();

    if ( map == nullptr ) {
      ofxLoopinEvent event("mapFuckup");
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
