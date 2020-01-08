#include "./Texture.hpp"

 void ofxLoopin::shader::Texture::addSubControls() {
  addSubControl("buffer", &buffer );
  addSubControl("minFilter", &minFilter );
  addSubControl("magFilter", &magFilter );
  addSubControl("wrapH", &wrapH );
  addSubControl("wrapV", &wrapV );
};

void ofxLoopin::shader::Texture::patchString( string value ) {
  const string bufferName = value; 
  buffer.patch( ofJson( bufferName ) );
};

void ofxLoopin::shader::Texture::patchLocal( const ofJson & value ) {
  if ( value.is_object() ) {
    if ( value.count("wrap") ) {
      wrapH.patch( value["wrap"] );
      wrapV.patch( value["wrap"] );
    }

    if ( value.count("filter") ) {
      minFilter.patch( value["filter"] );
      magFilter.patch( value["filter"] );
    }
  }
}

bool ofxLoopin::shader::Texture::hasTexture() {
  ofxLoopin::base::Buffer * bufferP = buffer.getPointer();
  if ( bufferP ) {
    return bufferP->isAllocated();
  }

  return false;
}


ofTexture * ofxLoopin::shader::Texture::getTexture() {
  stringstream description;
  description << buffer.key;

  if ( !hasTexture() ) {
    description << " NOT RENDERED";
    _bufferDescription = description.str();
    return nullptr;
  }

  ofxLoopin::base::Buffer * bufferP = buffer.getPointer();
  ofTexture * texture = bufferP->getTexture();

  if ( !texture || !texture->isAllocated() ) {
    description << " NOT ALLOCATED?!!";
    _bufferDescription = description.str();

    return nullptr;
  }

  description << " " << texture->getWidth() << "x" << texture->getHeight();
  description << " " << bufferP->format.getKey();
  description << " " << (char) ( 'A' + bufferP->getReadIndex() );

  _bufferDescription = description.str();

  texture->setTextureWrap( wrapH.getEnumValue(), wrapV.getEnumValue() );
  texture->setTextureMinMagFilter( minFilter.getEnumValue(), magFilter.getEnumValue() );

  return texture;
}


void ofxLoopin::shader::Texture::bindToShader( ofxLoopin::shader::Shader * shader ) {
  _shader = shader;
  _boundLocation = shader->_textureLocation++;
  // cerr << "bindToShader " << shader << " " << shader->_textureLocation << endl;
  bindTexture( getTexture() );
}


void ofxLoopin::shader::Texture::renderTexture( ofxLoopin::shader::Shader * shader, const ofRectangle & bounds ) {
  ofTexture * texture = getTexture();
  if ( texture ) {
    _shader = shader;
    _boundLocation = shader->_textureLocation++;
    bindTexture( texture );
    texture->draw( bounds.x, bounds.y, bounds.width, bounds.height );
  }
}

// void ofxLoopin::shader::Texture::bindSpecific( ofxLoopin::shader::Shader * shader, string key, int location ) {
//   // ofMatrix4x4 matrix;
//   // shader->shader.setUniformMatrix4f( key + "Matrix", matrix );

//   if ( !hasTexture() )
//     return;

//   _boundLocation = location;

//   ofxLoopin::base::Buffer * bufferP = buffer.getPointer();

//   if ( !bufferP )
//     return;

//   shader->shader.setUniform1i( key + "Rows", bufferP->rows );
//   shader->shader.setUniform1i( key + "Cols", bufferP->cols );

//   ofTexture * texture = getTexture();
//   bindTexture( shader, texture );
// }

void ofxLoopin::shader::Texture::bindTexture( ofTexture * texture ) {
  if ( !texture || !texture->isAllocated() )
    return;

  _texture = texture;

  _texture->setTextureWrap( wrapH.getEnumValue(), wrapV.getEnumValue() );
  _texture->setTextureMinMagFilter( minFilter.getEnumValue(), magFilter.getEnumValue() );
  _texture->bind( _boundLocation );

  if ( _shader ) {
    // cerr << "bindTexture " << path << " " << key << " " << _shader << " " << texture->getWidth() << "x" << texture->getHeight() << endl;

    _shader->shader.setUniformTexture( key + "Sampler", *texture, _boundLocation );
    _shader->shader.setUniform1i( key + "Width", texture->getWidth() );
    _shader->shader.setUniform1i( key + "Height", texture->getHeight() );
  }
};

void ofxLoopin::shader::Texture::unbind() {
  if ( _boundLocation != -1 ) {
    _boundLocation = -1;
    // if ( _texture ) {
    //   _texture->unbind();
    //   _texture = nullptr;
    // }
  }
}
