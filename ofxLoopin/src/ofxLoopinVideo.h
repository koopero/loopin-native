#pragma once

#include "ofxLoopinFile.h"
#include "ofxLoopinRender.h"


#include "ofVideoPlayer.h"

class ofxLoopinVideo : public ofxLoopinRender {
public:
  ofxLoopinControlEnum<ofLoopType, OF_LOOP_NONE> loop;

protected:
  void patchLocal( const Json::Value & value ) {
    cerr << "ofxLoopinVideo::patchLocal " << value << endl;

    if ( value.isMember("src") && value["src"].isString() ) {
      string videoPath = value["src"].asString();
      string absPath = ofxLoopinFile::find( videoPath );

      if ( absPath.size() ) {
        _video.load( absPath );
      } else {
        auto event = ofxLoopinEvent::fileNotFound( videoPath );
        dispatch( event );
      }
    }
  };

  void patchString( const string & value ) {
    Json::Value patch;
    patch["src"] = value;
    patchLocal( patch );
  };



  void readLocal( Json::Value & value ) {
    cerr << "ofxLoopinVideo::readLocal" << endl;
  };

  // virtual void readLocal( Json::Value & value ) {};


  void addSubControls() {
    // cerr << "ofxLoopinVideo::addSubControls " << key << endl;

    loop.setEnumKey( "none", OF_LOOP_NONE );
    loop.setEnumKey( "loop", OF_LOOP_NORMAL );
    loop.setEnumKey( "palindrome", OF_LOOP_PALINDROME );

    addSubControl( "loop", &loop );
  }

private:
  ofVideoPlayer _video;

};
