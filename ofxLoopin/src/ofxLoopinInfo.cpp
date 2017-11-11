#include "ofxLoopinInfo.h"

void ofxLoopinInfo::readLocal( Json::Value & value ) {
  value = getInfo();
}

Json::Value ofxLoopinInfo::getInfo() {
  Json::Value result;
  result["waveform"] = getInfoKey( "waveform" );
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
//
// Json::Value ofxLoopinInfo::getGLInfo() {
//   shared_ptr<ofBaseGLRenderer> renderer = dynamic_pointer_cast<ofBaseGLRenderer>( ofGetCurrentRenderer() );
//
//   Json::Value result;
//   result["VersionMajor"] = renderer->getGLVersionMajor();
//   result["VersionMinor"] = renderer->getGLVersionMinor();
//   return result;
// }
