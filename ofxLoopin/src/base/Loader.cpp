#include "./Loader.hpp"
#include "./File.hpp"


void ofxLoopin::base::Loader::patchLocal( const ofJson & value ) {
  bool shouldLoad = false;

  if ( value.is_string() ) {
    filePath = value.get<std::string>();
    shouldLoad = true;
  }

  if ( shouldLoad ) {
    load();
  }
};


string ofxLoopin::base::Loader::getFilePath() {
  return ofxLoopin::base::File::find( filePath );
};
