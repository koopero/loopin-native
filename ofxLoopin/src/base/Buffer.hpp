#pragma once

#include "./control/Control.hpp"
#include "./control/Bool.hpp"
#include "./control/Enum.hpp"
#include "./control/Number.hpp"
#include "./control/Numeric.hpp"
#include "./control/Event.hpp"
#include "./control/Map.hpp"

#include "ofMain.h"
#include "ofFbo.h"
#include "ofTexture.h"
#include "ofGraphics.h"


/** loopin/type/buffer/sub

width:
  type: integer
  min: 0
  max: 8192

height:
  type: integer
  min: 0
  max: 8192

format:
  type: options
*/

/** platform/GL/loopin/type/buffer/sub/format
  options:
    - rgba8
    - rgba16
    - rgba32f
    - rgb8
    - rgb16
    - rgb32f
**/


/** platform/ES/loopin/type/buffer/sub/format:
  options:
    - rgba
    - rgb
**/

namespace ofxLoopin { namespace base {

class BufferSettings {
public:
  int width;
  int height;
  GLint format;
  int cols;
  int rows;
};


class Buffer : public ofxLoopin::control::Control {
public:
  int boundIndex = -1;


  // Pixel size of buffer
  ofxLoopin::control::Numeric _width;
  ofxLoopin::control::Numeric _height;
  ofxLoopin::control::Bool useDepth;
  ofxLoopin::control::Int   cols = 1;
  ofxLoopin::control::Int   rows = 1;

  ofxLoopin::control::Number aspect = 1;

  #ifndef TARGET_OPENGLES
    ofxLoopin::control::Enum<int,GL_RGBA8> format;
  #else
    ofxLoopin::control::Enum<int,GL_RGBA> format;
  #endif

  bool ready() {
    return allocate( getWriteIndex() );
  };

  // Begins drawing to the current buffer.
  // If the buffer has not been allocated,
  // returns false and does nothing.
  bool begin();

  // Finishes drawing to the current buffer.
  void end();

  bool isAllocated() {
    return isAllocated( getReadIndex() );
  };
  bool isAllocated( size_t index  );

  ofTexture * getTexture() {
    return getTexture( getReadIndex() );
  };
  ofTexture * getTexture( size_t index );
  ofFbo & getFbo();

  void setTexture( const ofTexture & texture, bool resize = false );
  void setSize( int width, int height, GLint format = -1 );


  int getWidth();
  int getHeight();
  ofRectangle getArea();
  ofVec2f getSize();
  float getAspect() { return getWidth() / (float) getHeight(); };

  void draw( int width, int height, int x = 0, int y = 0 );

  void defaultSize() {
    defaultSize(
      ofRectangle( 0, 0,
        ofGetWindowWidth(),
        ofGetWindowHeight()
      )
    );
  };

  void defaultSize( ofRectangle area );

  bool sizeIsDefault();

  static int const MAX_SIZE = 12800;

  void flip();

  size_t getReadIndex();
  size_t getWriteIndex();

  bool bufferIsNew = true;

protected:
  void addSubControls() {
    addSubControl("aspect", &aspect );

    #ifndef TARGET_OPENGLES
      format.enumAddOption("rgba", GL_RGBA8 );
      format.enumAddOption("rgba8", GL_RGBA8 );
      format.enumAddOption("rgba16", GL_RGBA16 );
      format.enumAddOption("rgba32", GL_RGBA32F_ARB );
      format.enumAddOption("rgba32f", GL_RGBA32F_ARB );

      format.enumAddOption("rgb", GL_RGB8 );
      format.enumAddOption("rgb8", GL_RGB8 );
      format.enumAddOption("rgb16", GL_RGB16 );
      format.enumAddOption("rgb32", GL_RGB32F_ARB );
      format.enumAddOption("rgb32f", GL_RGB32F_ARB );
    #else
      // Much more limited options under ES
      format.enumAddOption("rgba", GL_RGBA );
      format.enumAddOption("rgb", GL_RGB );
    #endif
    addSubControl( "format", &format );

    addSubControl( "depth", &useDepth );

    addSubControl( "width", &_width );
    addSubControl( "height", &_height );

    addSubControl( "rows", &rows );
    addSubControl( "cols", &cols );
  }
  void readLocal( ofJson & value );

  void patchLocal( const ofJson & value ) {
    if ( value.is_number() ) {
      _width.patch( value );
      _height.patch( value );
    }
  };


private:
  int curIndex = 0;
  int lastWroteIndex = -1;
  ofFbo buffers[2];
  ofFbo::Settings _bufferSettings[2];

  bool allocate( int index );

};

bool BufferCompareSettings( const ofFbo::Settings &a, const ofFbo::Settings &b );

class Buffers : public ofxLoopin::control::Map<Buffer> {

};

class HasBuffers {
public:
  Buffers buffers;
  Buffers * __getMap() { return &buffers; }
};
}};