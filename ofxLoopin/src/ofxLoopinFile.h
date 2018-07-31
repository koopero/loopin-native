#pragma once

// #include "Poco/Path.h"

#include "ofFileUtils.h"

#include <string>
#include <vector>
#include "filesystem/path.hpp"

using namespace std;

class ofxLoopinFile {
public:
  static void addPath( const string & path ) {
    _paths.push_back( path );
  }

  static string find( const string & path ) {
    for ( auto & dir : _paths ) {
      auto pathAbs = boost::filesystem::absolute( path, dir );
      // pathAbs = pathAbs.resolve( path );

      ofFile _file = ofFile( pathAbs );
      if ( _file.exists() ) {
        return pathAbs.native();
      }
    }

    return "";
  };

  static string target( const string & path ) {
    string dir = _paths[0];
    auto pathAbs = boost::filesystem::absolute( path, dir );
    // pathAbs = pathAbs.resolve( path );
    // ofFile _file = ofFile( pathAbs );
    return pathAbs.native();
  };

  static string root() {
    return _paths[0];
  };
private:
  static std::vector<string> _paths;
};
