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
    FORMAT_BASE64,
    FORMAT_HEX
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

  string pixels;

  ofRectangle getBounds();
  void renderBuffer( ofxLoopinBuffer * buffer );
  void renderPixels( ofxLoopinBuffer * buffer );
  void outputPixels( ofxLoopinBuffer * buffer );

protected:
  string _lastPixels;

  string decodeInput();

  void updateLocal();

  void patchLocal( const Json::Value & value );
  void patchString( const string & value );
  string decodeHex( const string & input, int digits = 2 );

  void addSubControls() {
    addSubControl("buffer", &buffer );

    format.setEnumKey( "base64", FORMAT_BASE64 );
    format.setEnumKey( "hex", FORMAT_HEX );
    addSubControl("format", &format );

    input.setEnumKey( "change", INPUT_CHANGE );
    input.setEnumKey( "always", INPUT_ALWAYS );
    addSubControl("input", &input );

    output.setEnumKey( "none", OUTPUT_NONE );
    output.setEnumKey( "always", OUTPUT_ALWAYS );
    output.setEnumKey( "once", OUTPUT_ONCE );
    addSubControl("output", &output );

    addSubControl("channels", new ofxLoopinControlValue( &channels ) );
    addSubControl("pixels", new ofxLoopinControlValue( &pixels ) );
  };
};
