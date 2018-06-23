#include "ofxLoopinStdio.h"

void ofxLoopinStdio::start () {
  startThread();
}

bool EndsWith(const string& a, const string& b) {
    if (b.size() > a.size()) return false;
    return std::equal(a.begin() + a.size() - b.size(), a.end(), b.begin());
}

void ofxLoopinStdio::dispatch ( const ofxLoopinEvent & event ) {
  ofJson json;

  string path = event.path;
  if ( !EndsWith( path, "/" ) )
    path += "/";

  json["type"] = event.type;
  json["path"] = path;
  json["data"] = event.data;

  std::cerr << json.dump() << std::endl;
}


void ofxLoopinStdio::threadedFunction () {
  while ( isThreadRunning() ) {
    string line;

    //
    if ( std::cin.rdbuf()->in_avail() && std::getline( std::cin, line ) ) {
      if ( line.size() ) {
        // std::cerr << "ofxLoopinStdio::threadedFunction '" << line << "'" << std::endl;
        
        lock();
        lines_.push_back( line );
        unlock();
      }
    } else {
      sleep( 1 );
    }
  }
}

ofJson ofxLoopinStdio::getValue() {
  lock();
  value.clear();

  for (const string& line : lines_ ){
    ofJson delta = ofJson::parse( line );
    mergeValue( value, delta );
  }
  lines_.resize(0);
  unlock();

  return value;
}



void ofxLoopinStdio::mergeValue(ofJson& a, ofJson& b) {
  // a.merge_patch( b );
  if ( b.is_object() && !a.is_object() )
    a = ofJson();

  if (!a.is_object() || !b.is_object()) {
    a = b;
    return;
  }

  for ( ofJson::iterator it = b.begin(); it != b.end(); ++it ) {
    string key = it.key();
    mergeValue( a[key], b[key] );
  }
}
