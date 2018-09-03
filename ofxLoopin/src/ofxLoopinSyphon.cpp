#include "ofxLoopinSyphon.h"

ofJson ofxLoopinSyphonRoot::infoGet() {
  ofJson result;
  ofJson servers = ofJson::array();
  for ( int i = 0; i < syphonServerDirectory.size(); i ++ ) {
    auto item = syphonServerDirectory.getDescription( i );
    ofJson server;
    server["name"] = item.serverName;
    server["app"] = item.appName;
    servers[i] = server;
  }

  result["servers"] = servers;
  return result;    
};
  