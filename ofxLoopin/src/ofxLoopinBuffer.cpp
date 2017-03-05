#include "ofxLoopinBuffer.h"


bool ofxLoopinBuffer::isAllocated( size_t index ) {
  ofFbo & buffer = buffers[ index ];
  return buffer.isAllocated();
}


ofTexture * ofxLoopinBuffer::getTexture( size_t index ) {
  if ( !isAllocated( index ) )
    return nullptr;

  ofFbo & buffer = buffers[ index ];

  return &buffer.getTexture();
}

ofFbo & ofxLoopinBuffer::getFbo() {
  return buffers[getReadIndex()];
}

void ofxLoopinBuffer::setTexture( const ofTexture & texture, bool resize ) {
  if ( resize || sizeIsDefault() )
    setSize( texture.getWidth(), texture.getHeight() );

  if ( begin() ) {
    ofEnableBlendMode( OF_BLENDMODE_DISABLED );
    texture.draw( getArea() );
    end();
  }
}

void ofxLoopinBuffer::setSize( int width, int height, GLint format ) {
  width = width > MAX_SIZE ? MAX_SIZE : width < 0 ? 0 : width;
  height = height > MAX_SIZE ? MAX_SIZE : height < 0 ? 0 : height;

  _width.setValueHard( width );
  _height.setValueHard( height );

  if ( format != -1 ) {
    ofxLoopinBuffer::format.setEnumValue( format );
  }
}

ofRectangle ofxLoopinBuffer::getArea() {
  return ofRectangle( 0,0, getWidth(), getHeight() );
}

int ofxLoopinBuffer::getWidth() {
  return _width.getValueInt();
}

int ofxLoopinBuffer::getHeight() {
  return _height.getValueInt();
}

ofVec2f ofxLoopinBuffer::getSize() {
  return ofVec2f( getWidth(), getHeight() );
}

bool ofxLoopinBuffer::sizeIsDefault() {
  return getWidth() <= 0 || getHeight() <= 0;
}

void ofxLoopinBuffer::defaultSize( ofRectangle area ) {
  if ( sizeIsDefault() ) {
    setSize( area.getWidth(), area.getHeight() );
  }
}

void ofxLoopinBuffer::flip() {
  curIndex = curIndex ? 0 : 1;
}

size_t ofxLoopinBuffer::getReadIndex() {
  if ( lastWroteIndex >= 0 && lastWroteIndex != boundIndex ) {
    return lastWroteIndex;
  }

  int readIndex = boundIndex < 0 ? curIndex : boundIndex ? 0 : 1;
  return readIndex;
}

size_t ofxLoopinBuffer::getWriteIndex() {
  return curIndex;
}

bool ofxLoopinBuffer::allocate( int index ) {
  int width = getWidth();
  int height = getHeight();
  int format = ofxLoopinBuffer::format.getEnumValue();

  width = width > MAX_SIZE ? MAX_SIZE : width < 0 ? 0 : width;
  height = height > MAX_SIZE ? MAX_SIZE : height < 0 ? 0 : height;

  if ( !width || !height )
    return false;

  ofFbo & buffer = buffers[index];

  if ( !buffer.isAllocated()
    || width != buffer.getWidth()
    || height != buffer.getHeight()
    || _bufferFormats[index] != format
  ) {
    buffer.allocate( width, height, format );

    // buffer.begin();
    // ofClear( 0, 0 );
    // buffer.end();

    _bufferFormats[index] = format;
  }

  return width && height && buffer.isAllocated();
}

void ofxLoopinBuffer::draw( int width, int height, int x, int y ) {
  int index = getReadIndex();
  ofFbo & buffer = buffers[index];

  if ( buffer.isAllocated() ) {
    ofTexture &texture = buffer.getTexture();
    texture.draw( x,y, width, height );
  }
}

bool ofxLoopinBuffer::begin() {
  int index = getWriteIndex();

  if ( !allocate( index ) )
    return false;

  ofFbo & buffer = buffers[index];

  buffer.begin();
  boundIndex = index;

  return true;
}

void ofxLoopinBuffer::end() {
  if ( boundIndex >= 0 ) {
    ofFbo & buffer = buffers[boundIndex];
    lastWroteIndex = boundIndex;

    buffer.end();
    boundIndex = -1;
  }
}

void ofxLoopinBuffer::readLocal( Json::Value & value ) {
  value["width"] = getWidth();
  value["height"] = getHeight();
}
