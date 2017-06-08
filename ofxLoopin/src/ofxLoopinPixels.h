#pragma once

#include "ofImage.h"
#include "ofThread.h"

#include "ofxLoopinControlEnum.h"
#include "ofxLoopinRender.h"
#include "ofxLoopinFrame.h"
#include "ofxLoopinMap.h"

class ofxLoopinPixels : public ofxLoopinRender {
public:
  enum Format {
    FORMAT_HEX,
    FORMAT_HEX2,
    FORMAT_BASE64,
    FORMAT_FLOAT,
    FORMAT_DECIMAL,
    FORMAT_PERCENT
  };

  ofxLoopinControlEnum<ofxLoopinPixels::Format, FORMAT_BASE64> format;

  enum Input {
    INPUT_CHANGE,
    INPUT_ALWAYS
  };

  ofxLoopinControlEnum<ofxLoopinPixels::Input, INPUT_CHANGE> input;

  enum Output {
    OUTPUT_NONE,
    OUTPUT_ALWAYS,
    OUTPUT_ONCE
  };

  ofxLoopinControlEnum<ofxLoopinPixels::Output, OUTPUT_NONE> output;

  string channels = "rgb";

  ofxLoopinControlInt width = 0;
  ofxLoopinControlInt height = 0;


  string data;
  vector<float> floats;

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
  void patchLocal( const Json::Value & value );
  void patchString( const string & value );

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

  void addSubControls() {
    addSubControl("width", &width );
    addSubControl("height", &height );

    shader.key = "solidRGBA";
    addSubControl("shader", &shader );

    addSubControl("buffer", &buffer );

    format.setEnumKey( "hex", FORMAT_HEX );
    format.setEnumKey( "hex2", FORMAT_HEX2 );
    format.setEnumKey( "float", FORMAT_FLOAT );
    format.setEnumKey( "percent", FORMAT_PERCENT );
    format.setEnumKey( "decimal", FORMAT_DECIMAL );
    format.setEnumKey( "base64", FORMAT_BASE64 );
    addSubControl("format", &format );

    input.setEnumKey( "change", INPUT_CHANGE );
    input.setEnumKey( "always", INPUT_ALWAYS );
    addSubControl("input", &input );

    output.setEnumKey( "none", OUTPUT_NONE );
    output.setEnumKey( "always", OUTPUT_ALWAYS );
    output.setEnumKey( "once", OUTPUT_ONCE );
    addSubControl("output", &output );

    addSubControl("channels", new ofxLoopinControlValue( &channels ) );
    addSubControl("data", new ofxLoopinControlValue( &data ) );

  };
};
