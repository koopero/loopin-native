#include "./Buffer.hpp"


bool ofxLoopin::base::Buffer::isAllocated( size_t index ) {
  ofFbo & buffer = buffers[ index ];
  return buffer.isAllocated();
}


ofTexture * ofxLoopin::base::Buffer::getTexture( size_t index ) {
  if ( !isAllocated( index ) ) {
    return nullptr;
  }

  ofFbo & buffer = buffers[ index ];

  return &buffer.getTexture();
}

ofFbo & ofxLoopin::base::Buffer::getFbo() {
  return buffers[getReadIndex()];
}

void ofxLoopin::base::Buffer::setTexture( const ofTexture & texture, bool resize ) {
  if ( resize || sizeIsDefault() )
    setSize( texture.getWidth(), texture.getHeight() );

  if ( begin() ) {
    ofEnableBlendMode( OF_BLENDMODE_DISABLED );
    texture.draw( getArea() );
    end();
  }
}

void ofxLoopin::base::Buffer::setSize( int width, int height, GLint format ) {
  width = width > MAX_SIZE ? MAX_SIZE : width < 0 ? 0 : width;
  height = height > MAX_SIZE ? MAX_SIZE : height < 0 ? 0 : height;

  _width.setValueHard( width );
  _height.setValueHard( height );

  if ( format != -1 ) {
    ofxLoopin::base::Buffer::format.setEnumValue( format );
  }
}

ofRectangle ofxLoopin::base::Buffer::getArea() {
  return ofRectangle( 0,0, getWidth(), getHeight() );
}

int ofxLoopin::base::Buffer::getWidth() {
  return _width.getValueInt();
}

int ofxLoopin::base::Buffer::getHeight() {
  return _height.getValueInt();
}

ofVec2f ofxLoopin::base::Buffer::getSize() {
  return ofVec2f( getWidth(), getHeight() );
}

bool ofxLoopin::base::Buffer::sizeIsDefault() {
  return getWidth() <= 0 || getHeight() <= 0;
}

void ofxLoopin::base::Buffer::defaultSize( ofRectangle area ) {
  if ( sizeIsDefault() ) {
    setSize( area.getWidth(), area.getHeight() );
  }
}

void ofxLoopin::base::Buffer::flip() {
  curIndex = curIndex ? 0 : 1;
}

size_t ofxLoopin::base::Buffer::getReadIndex() {
  if ( lastWroteIndex >= 0 && lastWroteIndex != boundIndex ) {
    return lastWroteIndex;
  }

  int readIndex = boundIndex < 0 ? curIndex : boundIndex ? 0 : 1;
  return readIndex;
}

size_t ofxLoopin::base::Buffer::getWriteIndex() {
  return curIndex;
}

// Replace ofFbo::Settings operator!=, since it's noisy.
bool ofxLoopin::base::BufferCompareSettings( const ofFbo::Settings &a, const ofFbo::Settings &b ) {
  if ( a.width != b.width ) return false;
  if ( a.height != b.height ) return false;
  if ( a.useDepth != b.useDepth ) return false;
  if ( a.internalformat != b.internalformat ) return false;

  return true;
}

bool ofxLoopin::base::Buffer::allocate( int index ) {
  int width = getWidth();
  int height = getHeight();
  int format = ofxLoopin::base::Buffer::format.getEnumValue();

  width = width > MAX_SIZE ? MAX_SIZE : width < 0 ? 0 : width;
  height = height > MAX_SIZE ? MAX_SIZE : height < 0 ? 0 : height;

  if ( !width || !height )
    return false;

  ofFbo & buffer = buffers[index];

  ofFbo::Settings settings;
  settings.width = width;
  settings.height = height;
  settings.internalformat = format;
  settings.useDepth = useDepth.getValue();

  if ( !buffer.isAllocated()
    || !ofxLoopin::base::BufferCompareSettings( settings, _bufferSettings[index] )
  ) {
    buffer.allocate( settings );
    bufferIsNew = true;
    _bufferSettings[index] = settings;
  }

  return width && height && buffer.isAllocated();
}

void ofxLoopin::base::Buffer::draw( int width, int height, int x, int y ) {
  int index = getReadIndex();
  ofFbo & buffer = buffers[index];

  if ( buffer.isAllocated() ) {
    ofTexture &texture = buffer.getTexture();
    texture.draw( x,y, width, height );
  }
}

bool ofxLoopin::base::Buffer::begin() {
  int index = getWriteIndex();

  if ( !allocate( index ) )
    return false;

  ofFbo & buffer = buffers[index];

  buffer.begin();
  boundIndex = index;

  return true;
}

void ofxLoopin::base::Buffer::end() {
  if ( boundIndex >= 0 ) {
    ofFbo & buffer = buffers[boundIndex];
    lastWroteIndex = boundIndex;

    buffer.end();
    boundIndex = -1;
  }
}

void ofxLoopin::base::Buffer::readLocal( ofJson & value ) {
  int index = getReadIndex();
  ofFbo & buffer = buffers[index];

  if ( buffer.isAllocated() ) {
    value["width"] = buffer.getWidth();
    value["height"] = buffer.getHeight();
    value["allocated"] = true;
  } else {
    value["width"] = getWidth();
    value["height"] = getHeight();
    value["allocated"] = false;
  }
}
