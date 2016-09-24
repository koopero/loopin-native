#include "ofxLoopinLoader.h"

#include "ofxLoopinFile.h"


void ofxLoopinLoader::patchLocal( const Json::Value & value ) {
  bool shouldLoad = false;

  if ( value.isString() ) {
    filePath = value.asString();
    shouldLoad = true;
  }

  if ( shouldLoad ) {
    load();
  }
};


string ofxLoopinLoader::getFilePath() {
  return ofxLoopinFile::find( filePath );
};
