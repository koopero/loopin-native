#include "ofxLoopinImage.h"
#include "ofxLoopinFile.h"


void ofxLoopinImage::updateLocal() {
  // TODO
  if ( src != _loaded || reload ) {
    load( src );
  }
}

void ofxLoopinImage::load( string filePath ) {

  _loaded = filePath;

  ofxLoopinEvent event;

  string absolutePath = ofxLoopinFile::find( filePath );

  if ( !absolutePath.size() ) {
    auto errorEvent = ofxLoopinEvent::fileNotFound( filePath );
    dispatch( errorEvent );
    return;
  }


  event.data["file"] = absolutePath;

  bool status = ofLoadImage( texture, absolutePath );

  if ( status ) {
    event.type = "done";
    event.data["loaded"] = true;
    event.data["error"] = Json::Value::null;
    event.data["width"] = texture.getWidth();
    event.data["height"] = texture.getHeight();
  } else {
    event.type = "error";
  }

  dispatch( event );
}


void ofxLoopinImage::render( ofxLoopinBuffer * buffer ) {

  if ( !buffer )
    buffer = getBuffer( true );

  if ( texture.isAllocated() ) {
    buffer->setTexture( texture, opt_resize );
    texture.clear();
  }
}
