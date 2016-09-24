#pragma once

#include "ofxLoopinControl.h"
#include "ofxLoopinFile.h"
#include "ofxLoopinFrame.h"


#include "ofGraphics.h"

#include <unistd.h>

class ofxLoopinOSD : public ofxLoopinControl {
public:
  bool enabled = true;

  string defaultString = {
    "   fps: %fps\n"
    " files: %files\n"
    "  show: %show\n"
    "window: %window\n"
    "  host: %hostname\n"
    "client: %client"
  };

  string text;
  string show;
  string hostname;
  string client;


  void setFrame( const ofxLoopinFrame & frame ) {
    _frame = frame;
  }

  void draw() {
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

protected:

  ofxLoopinFrame _frame;

  void addSubControls() {
    addSubControl( "enabled", new ofxLoopinControlValue( &enabled ) );
    addSubControl( "text", new ofxLoopinControlValue( &text ) );
    addSubControl( "client", new ofxLoopinControlValue( &client ) );



    // Get hostname now, since this only happens once.
    char buf[256];
    gethostname( buf, 255 );

    hostname = buf;
  };

private:
  void templatize( string & str, const string & key, float value ) {
    string valueStr = ofToString( value, 4 );
    templatize( str, key, valueStr );
  }
  void templatize( string & str, const string & key, const string & replacement ) {
    string::size_type pos = 0;

    string oldStr = "%"+key;

    while((pos = str.find(oldStr, pos)) != std::string::npos){
       str.replace(pos, oldStr.length(), replacement);
       pos += replacement.length();
    }
  }

};
