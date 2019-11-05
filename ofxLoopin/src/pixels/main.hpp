#pragma once

#include "ofImage.h"
#include "ofThread.h"

#include "./control/Enum.hpp"
#include "../render/Render.hpp"
#include "../clock/Frame.hpp"
#include "./control/Map.hpp"
#include "../shader/Shader.hpp"
#include "../control/Box.hpp"


namespace ofxLoopin { namespace pixels {

class Render;

class Map : public ofxLoopin::render::Renders<Render> {};

class Render : public ofxLoopin::render::Render {
public:
  enum Format {
    FORMAT_HEX,
    FORMAT_HEX2,
    FORMAT_BASE64,
    FORMAT_FLOAT,
    FORMAT_DECIMAL,
    FORMAT_PERCENT
  };

  ofxLoopin::control::Enum<Format, FORMAT_BASE64> format;

  enum Input {
    INPUT_CHANGE,
    INPUT_NONE,
    INPUT_ALWAYS
  };

  ofxLoopin::control::Enum<Input, INPUT_CHANGE> input;

  enum Output {
    OUTPUT_NONE,
    OUTPUT_ALWAYS,
    OUTPUT_ONCE
  };

  ofxLoopin::control::Enum<Output, OUTPUT_NONE> output;

  string channels = "rgb";

  // ofxLoopin::control::Int width = 0;
  // ofxLoopin::control::Int height = 0;

  ofxLoopin::control::Box box;
  ofxLoopin::control::Bool replace;


  string data;
  std::vector<float> floats;

  void bufferToFloats( ofxLoopin::base::Buffer * buffer );


  ofRectangle getBounds();
  GLint getFormat();
  void renderBuffer( ofxLoopin::base::Buffer * buffer );
  void renderFloats( ofxLoopin::base::Buffer * buffer );

  void outputPixels( ofxLoopin::base::Buffer * buffer );

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

  void maybeOutputBuffer( ofxLoopin::base::Buffer * buffer );
  void addSubControls();

  static ofxLoopin::shader::Shader shader;
};



// end of namespace
}}
