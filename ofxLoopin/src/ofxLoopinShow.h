#pragma once

#include "ofxLoopinTexture.h"

/** loopin/type/show:
  type: texture
*/
class ofxLoopinShow : public ofxLoopinTexture {
public:
  void draw() {
    stringstream description;

    description << buffer.key;

    if ( !hasTexture() ) {
      description << " NO TEXTURE!";
      _bufferDescription = description.str();
      return;
    }

    ofRectangle area = ofRectangle( 0, 0, ofGetWindowWidth(), ofGetWindowHeight() );

    ofxLoopinBuffer * bufferP = buffer.getPointer();
    ofTexture * texture = bufferP->getTexture();

    if ( !texture || !texture->isAllocated() ) {
      description << " NOT ALLOCATED?!!";
      _bufferDescription = description.str();

      return;
    }


    description << " ( " << texture->getWidth() << "x" << texture->getHeight();
    description << " " << bufferP->format.getKey();
    description << " )";
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
