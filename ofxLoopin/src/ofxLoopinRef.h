#pragma once

#include "ofxLoopinMap.h"
#include "ofxLoopinRoot.h"
#include <assert.h>

template <class TYPE, class HAS>
class ofxLoopinRef : public ofxLoopinControl {
public:
  string key;

  TYPE * getPointer( bool create = true ) {

    if ( root == nullptr ){
      ofxLoopinEvent event("rooFuckup");
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

protected:
  void patchString( const string & value ) {
    key = value;
  }

  void readLocal( Json::Value & value ) {
    if ( key.size() )
      value = key;
    else
      value = Json::nullValue;
  }

private:

};
