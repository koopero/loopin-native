#include "./OSD.hpp"

void ofxLoopin::window::OSD::setFrame( const ofxLoopinFrame & frame ) {
  _frame = frame;
}

void ofxLoopin::window::OSD::draw() {
  if ( !enabled )
    return;

  string str = text.size() ? text : defaultString;
  templatize( str, "fps", ofGetFrameRate() );
  templatize( str, "files", ofxLoopinFile::root() );
  templatize( str, "show", show );
  templatize( str, "hostname", hostname );
  templatize( str, "client", client );
  templatize( str, "window", ofToString( ofGetWindowWidth() ) + "x" + ofToString( ofGetWindowHeight() ));


  ofPoint position = ofPoint( 16, 24 );
  ofColor background = ofColor( 0,0,0, 192 );
  ofColor foreground = ofColor( 255,255,255 );

  ofEnableBlendMode( OF_BLENDMODE_ALPHA );
  glDisable( GL_CULL_FACE );
  ofDrawBitmapStringHighlight( str, position, background, foreground );
}

void ofxLoopin::window::OSD::addSubControls() {
  addSubControl( "enabled", new ofxLoopin::control::Value( &enabled ) );
  addSubControl( "text", new ofxLoopin::control::Value( &text ) );
  addSubControl( "client", new ofxLoopin::control::Value( &client ) );

  // Get hostname now, since this only happens once.
  char buf[256];
  gethostname( buf, 255 );

  hostname = buf;
};

void ofxLoopin::window::OSD::templatize( string & str, const string & key, float value ) {
  string valueStr = ofToString( value, 4 );
  templatize( str, key, valueStr );
}

void ofxLoopin::window::OSD::templatize( string & str, const string & key, const string & replacement ) {
  string::size_type pos = 0;

  string oldStr = "%"+key;

  while((pos = str.find(oldStr, pos)) != std::string::npos){
      str.replace(pos, oldStr.length(), replacement);
      pos += replacement.length();
  }
}