#pragma once

#include "ofxLoopinTexture.h"

class ofxLoopinShow : public ofxLoopinTexture {
public:
  void draw() {
    if ( !hasTexture() ) {
      _bufferDescription = "NO TEXTURE!";
      return;
    }

    ofRectangle area = ofRectangle( 0,0,ofGetWindowWidth(), ofGetWindowHeight() );

    ofxLoopinBuffer * bufferP = buffer.getPointer();
    ofTexture * texture = bufferP->getTexture();

    if ( !texture || !texture->isAllocated() ) {
      _bufferDescription = "NOT ALLOCATED?!!";
      return;
    }

    stringstream description;
    description << buffer.key << " (" << texture->getWidth() << "x" << texture->getHeight() << ")";

    _bufferDescription = description.str();

    texture->setTextureWrap( wrapH.getEnumValue(), wrapV.getEnumValue() );
    texture->setTextureMinMagFilter( minFilter.getEnumValue(), magFilter.getEnumValue() );
    texture->draw( area );
  }

  string getBufferDescription() {
    return _bufferDescription;
  };

private:
  string _bufferDescription;
};
