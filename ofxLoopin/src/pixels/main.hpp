#pragma once

#include "ofImage.h"
#include "ofThread.h"

#include "ofxLoopinControlEnum.h"
#include "ofxLoopinRender.h"
#include "ofxLoopinFrame.h"
#include "ofxLoopinMap.h"
#include "ofxLoopinShader.h"

namespace ofxLoopin { namespace pixels {

class Render;

class Map : public ofxLoopinRenders<Render> {};

class Render : public ofxLoopinRender {
public:
  enum Format {
    FORMAT_HEX,
    FORMAT_HEX2,
    FORMAT_BASE64,
    FORMAT_FLOAT,
    FORMAT_DECIMAL,
    FORMAT_PERCENT
  };

  ofxLoopinControlEnum<Format, FORMAT_BASE64> format;

  enum Input {
    INPUT_CHANGE,
    INPUT_NONE,
    INPUT_ALWAYS
  };

  ofxLoopinControlEnum<Input, INPUT_CHANGE> input;

  enum Output {
    OUTPUT_NONE,
    OUTPUT_ALWAYS,
    OUTPUT_ONCE
  };

  ofxLoopinControlEnum<Output, OUTPUT_NONE> output;

  string channels = "rgb";

  ofxLoopinControlInt width = 0;
  ofxLoopinControlInt height = 0;


  string data;
  std::vector<float> floats;

  void bufferToFloats( ofxLoopinBuffer * buffer );


  ofRectangle getBounds();
  GLint getFormat();
  void renderBuffer( ofxLoopinBuffer * buffer );
  void renderFloats( ofxLoopinBuffer * buffer );

  void outputPixels( ofxLoopinBuffer * buffer );

protected:
  string _lastPixels;

  int readWidth = 0;
  int readHeight = 0;

  bool _isDirty = false;

  void updateLocal();
  void patchLocal( const ofJson & value );
  void patchString( string value );

  bool decodeInput();
  void decodeNumeric( float divider = 1 );
  void decodeHex( int digits = 2 );
  void decodeBinary( const string &data );

  void encode();
  void encodeBase64();
  void encodeHex( int digits );
  void encodeNumeric( float divider );
  void encodeBinary();


  void dispatchData();

  void maybeOutputBuffer( ofxLoopinBuffer * buffer );
  void addSubControls();

  static ofxLoopinShader shader;
};



// end of namespace
}}
