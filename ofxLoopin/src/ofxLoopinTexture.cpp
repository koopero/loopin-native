#include "ofxLoopinTexture.h"


void ofxLoopinTexture::bindToShader( ofxLoopinShader * shader ) {

  ofMatrix4x4 matrix;
  shader->shader.setUniformMatrix4f( key + "Matrix", matrix );

  if ( !hasTexture() )
    return;

  _boundLocation = shader->_textureLocation++;

  ofxLoopinBuffer * bufferP = buffer.getPointer();

  if ( !bufferP )
    return;

  shader->shader.setUniform1i( key + "Rows", bufferP->rows );
  shader->shader.setUniform1i( key + "Cols", bufferP->cols );

  ofTexture * texture = bufferP->getTexture();

  if ( !texture || !texture->isAllocated() )
    return;


  texture->setTextureWrap( wrapH.getEnumValue(), wrapV.getEnumValue() );
  texture->setTextureMinMagFilter( minFilter.getEnumValue(), magFilter.getEnumValue() );
  texture->bind( _boundLocation );

  shader->shader.setUniformTexture( key + "Sampler", *texture, _boundLocation );
  shader->shader.setUniform1i( key + "Width", texture->getWidth() );
  shader->shader.setUniform1i( key + "Height", texture->getHeight() );
}

void ofxLoopinTexture::unbind() {
  if ( _boundLocation != -1 ) {
    _boundLocation = -1;

    ofxLoopinBuffer * bufferP = buffer.getPointer();

    if ( !bufferP )
      return;

    ofTexture * texture = bufferP->getTexture();

    if ( !texture || !texture->isAllocated() )
      return;
  }
}
