#include "./Stdio.hpp"

void ofxLoopin::base::Stdio::start () {
  startThread();
}

bool EndsWith(const string& a, const string& b) {
  if (b.size() > a.size()) return false;
    return std::equal(a.begin() + a.size() - b.size(), a.end(), b.begin());
}

void ofxLoopin::base::Stdio::dispatch ( const ofxLoopin::control::Event & event ) {
  ofJson json;

  string path = event.path;
  if ( !EndsWith( path, "/" ) )
    path += "/";

  json["type"] = event.type;
  json["path"] = path;
  json["data"] = event.data;

  std::cerr << json.dump() << std::endl;
}


void ofxLoopin::base::Stdio::threadedFunction () {
  while ( isThreadRunning() ) {
    string line;

    if ( std::getline( std::cin, line ) ) {
      if ( line.size() ) {
        lock();
        lines_.push_back( line );
        unlock();
      }
    } else {
      sleep( 1 );
    }
  }
}

ofJson ofxLoopin::base::Stdio::getValue() {
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



void ofxLoopin::base::Stdio::mergeValue(ofJson& a, ofJson& b) {
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
