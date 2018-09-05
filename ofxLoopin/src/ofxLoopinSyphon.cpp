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


ofRectangle ofxLoopinSyphon::getBounds() {
  return ofRectangle( 0, 0, 640, 480 );

  return ofRectangle( 0, 0, syphonClient.getWidth(), syphonClient.getHeight() );
}

void ofxLoopinSyphon::renderBuffer( ofxLoopinBuffer * buffer ) {
  maybeOutputBuffer( buffer );



  if ( mode.getEnumValue() != MODE_CLIENT ) {
    return;
  }

  // if ( name != syphonClient.getServerName() ) {
  //   syphonClient.setServerName( name );
  // }

  // if (  ) {
  //   syphonClient.setApplicationName( app );
  // }

  if ( !syphonClient.isSetup() ) 
    syphonClient.setup();

  if ( name != syphonClient.getServerName() || app != syphonClient.getApplicationName() ) {
    // cerr << "ofxLoopinSyphon::renderBuffer init client " << endl;
    syphonClient.set( name, app );
  }

  // cerr << "ofxLoopinSyphon::renderBuffer " << name << " ap: " << syphonClient.getApplicationName() << " " << app << " " << getBounds() << endl;

  syphonClient.bind();
  ofTexture & texture = syphonClient.getTexture();
  ofRectangle bounds = ofRectangle( 0,0, texture.getWidth(), texture.getHeight() );
  // cerr << "ofxLoopinSyphon::renderBuffer " << name << " ap: " << syphonClient.getApplicationName() << " " << app << " " << bounds << endl;

  buffer->setTexture( texture, true );
  syphonClient.unbind();
}

void ofxLoopinSyphon::maybeOutputBuffer( ofxLoopinBuffer * buffer ) {
  if ( !buffer || !buffer->isAllocated() ) {
    // TODO: Error
    return;
  }

  if ( mode.getEnumValue() != MODE_SERVER ) {
    return;
  }

  ofTexture * texture = buffer->getTexture();

  if ( texture ) {
    syphonServer.setName( name );
    syphonServer.publishTexture( texture );
  }
  
  // bufferToFloats( buffer );
  // encode();
  // dispatchData();
}
