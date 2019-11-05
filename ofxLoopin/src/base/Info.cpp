#include "./Info.hpp"

void ofxLoopin::base::Info::readLocal( ofJson & value ) {
  value = getInfo();
}

ofJson ofxLoopin::base::Info::getInfo() {
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

ofJson ofxLoopin::base::Info::getInfoKey( const string & key ) {
  ofJson result;

  if ( !root )
    return result;

  map< string, ofxLoopin::control::Control *> subs = root->getSubs();

  if ( subs.count( key ) ) {
    ofxLoopin::base::HasInfo * hasInfo = dynamic_cast<ofxLoopin::base::HasInfo*>( subs[ key ] );

    if ( hasInfo ) {
      result = hasInfo->infoGet();
    }
  }

  return result;

}
