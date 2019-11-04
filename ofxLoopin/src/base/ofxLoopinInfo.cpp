#include "ofxLoopinInfo.h"

void ofxLoopinInfo::readLocal( ofJson & value ) {
  value = getInfo();
}

ofJson ofxLoopinInfo::getInfo() {
  ofJson result;

  map< string, ofxLoopin::control::Control *> subs = root->getSubs();

  for ( auto it = subs.begin(); it != subs.end(); it ++ ) {
    string key = it->first;
    ofJson keyResult = getInfoKey( key );

    if ( keyResult.is_object() )
      result[key] = keyResult;
  }
  return result;
}

ofJson ofxLoopinInfo::getInfoKey( const string & key ) {
  ofJson result;

  if ( !root )
    return result;

  map< string, ofxLoopin::control::Control *> subs = root->getSubs();

  if ( subs.count( key ) ) {
    ofxLoopinHasInfo * hasInfo = dynamic_cast<ofxLoopinHasInfo*>( subs[ key ] );

    if ( hasInfo ) {
      result = hasInfo->infoGet();
    }
  }

  return result;

}
