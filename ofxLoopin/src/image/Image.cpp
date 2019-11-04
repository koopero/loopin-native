#include "./Image.hpp"
#include "ofxLoopinFile.h"


void ofxLoopinImage::updateLocal() {
  // TODO

}

void ofxLoopinImage::load( string filePath ) {

  _loaded = filePath;
  _dirty = false;

  ofxLoopin::control::Event event;

  string absolutePath = ofxLoopinFile::find( filePath );

  if ( !absolutePath.size() ) {
    auto errorEvent = ofxLoopin::control::Event::fileNotFound( filePath );
    dispatch( errorEvent );
    return;
  }


  event.data["file"] = absolutePath;

  bool status = ofLoadImage( texture, absolutePath );

  if ( status ) {
    event.type = "done";
    event.data["loaded"] = true;
    event.data["error"] = ofJson();
    event.data["width"] = texture.getWidth();
    event.data["height"] = texture.getHeight();
  } else {
    event.type = "error";
  }

  dispatch( event );
}


void ofxLoopinImage::renderBuffer( ofxLoopinBuffer * buffer ) {
  if ( src != _loaded || _dirty ) {
    load( src );
  }

  if ( !texture.isAllocated() )
    return;

  if ( !buffer )
    buffer = getBuffer( true );

  ofRectangle size = ofRectangle( 0, 0, texture.getWidth(), texture.getHeight() );
  ofRectangle cropRect = crop.getFittedRectangle( size );

  // if ( cropRect.getArea() <= 0 )
    // return;

  if ( replace ) {
    buffer->setSize( cropRect.getWidth(), cropRect.getHeight() );
  } else {
    buffer->defaultSize( cropRect );
  }

  ofRectangle bufferArea = buffer->getArea();
  ofRectangle drawArea = box.getFittedRectangle( bufferArea );

  buffer->begin();


  ofEnableBlendMode( OF_BLENDMODE_DISABLED );
  texture.drawSubsection(
    drawArea.getX(),
    drawArea.getY(),
    drawArea.getWidth(),
    drawArea.getHeight(),
    cropRect.getX(),
    cropRect.getY(),
    cropRect.getWidth(),
    cropRect.getHeight()
  );
  buffer->end();
  texture.clear();
}
