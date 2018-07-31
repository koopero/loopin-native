#include "ofxLoopinStdio.h"

void ofxLoopinStdio::start () {
  startThread();
}

bool EndsWith(const string& a, const string& b) {
    if (b.size() > a.size()) return false;
    return std::equal(a.begin() + a.size() - b.size(), a.end(), b.begin());
}

void ofxLoopinStdio::dispatch ( const ofxLoopinEvent & event ) {
  Json::Value json = Json::objectValue;

  string path = event.path;
  if ( !EndsWith( path, "/" ) )
    path += "/";

  json["type"] = event.type;
  json["path"] = path;
  json["data"] = event.data;

  std::cerr << jsonWriter.write( json );
}


void ofxLoopinStdio::threadedFunction () {
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

Json::Value ofxLoopinStdio::getValue() {
  lock();
  value.clear();

  for (const string& line : lines_ ){
    Json::Reader reader;
    Json::Value delta;
    reader.parse( line, delta, false );
    mergeValue( value, delta );
  }
  lines_.resize(0);
  unlock();

  return value;
}



void ofxLoopinStdio::mergeValue(Json::Value& a, Json::Value& b) {
    if ( b.isObject() && !a.isObject() )
      a = Json::Value( Json::objectValue );

    if (!a.isObject() || !b.isObject()) return;

    for (const auto& key : b.getMemberNames()) {
        if (a[key].isObject()) {
            mergeValue(a[key], b[key]);
        } else {
            a[key] = b[key];
        }
    }
}
