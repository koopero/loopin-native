#include "ofxLoopinInfo.h"

void ofxLoopinInfo::readLocal( Json::Value & value ) {
  value = getInfo();
}

Json::Value ofxLoopinInfo::getInfo() {
  Json::Value result;

  map< string, ofxLoopinControl *> subs = root->getSubs();

  for ( auto it = subs.begin(); it != subs.end(); it ++ ) {
    string key = it->first;
    Json::Value keyResult = getInfoKey( key );

    if ( keyResult.isObject() )
      result[key] = keyResult;
  }
  return result;
}

Json::Value ofxLoopinInfo::getInfoKey( const string & key ) {
  Json::Value result;

  if ( !root )
    return result;

  map< string, ofxLoopinControl *> subs = root->getSubs();

  if ( subs.count( key ) ) {
    ofxLoopinHasInfo * hasInfo = dynamic_cast<ofxLoopinHasInfo*>( subs[ key ] );

    if ( hasInfo ) {
      result = hasInfo->infoGet();
    }
  }

  return result;

}
