#pragma once

#include "Poco/Path.h"

#include "ofFileUtils.h"

#include <string>
#include <vector>

using namespace std;

class ofxLoopinFile {
public:
  static void addPath( const Poco::Path & path ) {
    _paths.push_back( path );
  }

  static string find( const Poco::Path & path ) {
    for ( auto & dir : _paths ) {
      Poco::Path pathAbs = dir;
      pathAbs = pathAbs.resolve( path );

      ofFile _file = ofFile( pathAbs.toString() );
      if ( _file.exists() ) {
        return pathAbs.toString();
      }
    }

    return "";
  };

  static string target( const Poco::Path & path ) {
    Poco::Path dir = _paths[0];
    return dir.resolve( path ).toString();
  };

  static string root() {
    return _paths[0].toString();
  };
private:
  static vector<Poco::Path> _paths;
};
