#pragma once

#include "ofxLoopinControl.h"
#include "ofxLoopinControlEnum.h"
#include "ofxLoopinControlNumber.h"
#include "ofxLoopinControlNumeric.h"
#include "ofxLoopinEvent.h"
#include "ofxLoopinMap.h"

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


class ofxLoopinBuffer : public ofxLoopinControl {
public:
  // Pixel size of buffer
  ofxLoopinControlNumeric _width;
  ofxLoopinControlNumeric _height;

  ofxLoopinControlNumber aspect = 1;

  // Format of buffer ( not implemented )
  #ifndef TARGET_OPENGLES
    ofxLoopinControlEnum<int,GL_RGBA8> format;
  #else
    ofxLoopinControlEnum<int,GL_RGBA> format;
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

  void draw( int width, int height );

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

protected:
  void addSubControls() {
    addSubControl("aspect", &aspect );

    #ifndef TARGET_OPENGLES
      format.setEnumKey("rgba", GL_RGBA8 );
      format.setEnumKey("rgba8", GL_RGBA8 );
      format.setEnumKey("rgba16", GL_RGBA16 );
      format.setEnumKey("rgba32", GL_RGBA32F_ARB );
      format.setEnumKey("rgba32f", GL_RGBA32F_ARB );

      format.setEnumKey("rgb", GL_RGB8 );
      format.setEnumKey("rgb8", GL_RGB8 );
      format.setEnumKey("rgb16", GL_RGB16 );
      format.setEnumKey("rgb32", GL_RGB32F_ARB );
      format.setEnumKey("rgb32f", GL_RGB32F_ARB );
    #else
      // Much more limited options under ES
      format.setEnumKey("rgba", GL_RGBA );
      format.setEnumKey("rgb", GL_RGB );
    #endif

    addSubControl( "format", &format );

    addSubControl( "width", &_width );
    addSubControl( "height", &_height );
  }
  void readLocal( Json::Value & value );

private:
  int curIndex = 0;
  int boundIndex = -1;
  int lastWroteIndex = -1;
  ofFbo buffers[2];
  int _bufferFormats[2] = { -1, -1 };

  bool allocate( int index );
};

class ofxLoopinBuffers : public ofxLoopinMap<ofxLoopinBuffer> {

};

class ofxLoopinHasBuffers {
public:
  ofxLoopinBuffers buffers;
  ofxLoopinBuffers * __getMap() { return &buffers; }
};
