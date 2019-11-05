#include "./Syphon.hpp"

#ifdef LOOPIN_SYPHON

ofJson ofxLoopin::misc::SyphonRoot::infoGet() {
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


ofRectangle ofxLoopin::misc::Syphon::getBounds() {
  return ofRectangle( 0, 0, 640, 480 );

  return ofRectangle( 0, 0, syphonClient.getWidth(), syphonClient.getHeight() );
}

void ofxLoopin::misc::Syphon::renderBuffer( ofxLoopin::base::Buffer * buffer ) {
  maybeOutputBuffer( buffer );



  if ( mode.getEnumValue() != MODE_CLIENT ) {
    return;
  }

  if ( !syphonClient.isSetup() ) 
    syphonClient.setup();

  if ( name != syphonClient.getServerName() || app != syphonClient.getApplicationName() ) {
    // cerr << "ofxLoopin::misc::Syphon::renderBuffer init client " << endl;
    syphonClient.set( name, app );
  }

  // cerr << "ofxLoopin::misc::Syphon::renderBuffer " << name << " ap: " << syphonClient.getApplicationName() << " " << app << " " << getBounds() << endl;

  syphonClient.bind();
  ofTexture & texture = syphonClient.getTexture();
  ofRectangle bounds = ofRectangle( 0,0, texture.getWidth(), texture.getHeight() );
  // cerr << "ofxLoopin::misc::Syphon::renderBuffer " << name << " ap: " << syphonClient.getApplicationName() << " " << app << " " << bounds << endl;

  buffer->setTexture( texture, true );
  syphonClient.unbind();
}

void ofxLoopin::misc::Syphon::maybeOutputBuffer( ofxLoopin::base::Buffer * buffer ) {
  if ( !buffer || !buffer->isAllocated() ) {
    // TODO: Error
    return;
  }

  if ( mode.getEnumValue() != MODE_SERVER ) {
    return;
  }

  buffer->flip();
  ofTexture * texture = buffer->getTexture();

  if ( texture ) {
    syphonServer.setName( name );
    syphonServer.publishTexture( texture );
    // cerr << "Publish texture" << endl;
  }
  
  // bufferToFloats( buffer );
  // encode();
  // dispatchData();
}

#endif