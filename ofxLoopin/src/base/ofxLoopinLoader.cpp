#include "ofxLoopinLoader.h"

#include "ofxLoopinFile.h"


void ofxLoopinLoader::patchLocal( const ofJson & value ) {
  bool shouldLoad = false;

  if ( value.is_string() ) {
    filePath = value.get<std::string>();
    shouldLoad = true;
  }

  if ( shouldLoad ) {
    load();
  }
};


string ofxLoopinLoader::getFilePath() {
  return ofxLoopinFile::find( filePath );
};
