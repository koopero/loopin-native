#pragma once

#include "ofMain.h"
#include "../control/Enum.hpp"

namespace ofxLoopin { namespace pixels {
class Data {
public:
  enum Encoding {
    ENCODING_HEX,
    ENCODING_HEX2,
    ENCODING_BASE64,
    ENCODING_FLOAT,
    ENCODING_DECIMAL,
    ENCODING_PERCENT
  };

  ofxLoopin::control::Enum<Encoding, ENCODING_HEX> encoding;
  int width = 0;
  int height = 0;
  string channels = "rgb";
  string data;
  vector<float> floats;
  ofFloatPixels pixels;

  GLint getGLFormat();
  bool dataToFloats();
  void floatsToPixels();
  void pixelsToFloats( const ofFloatPixels & pixels );
  void pixelsToFloats() { pixelsToFloats( pixels ); };

  void setFloat( int index, float value );

protected:
  bool _isDirty = false;
  void decodeNumeric( float divider = 1 );
  void decodeHex( int digits = 2 );
  void decodeBinary( const string &data );
  void encode();
  void encodeBase64();
  void encodeHex( int digits );
  void encodeNumeric( float divider );
  void encodeBinary();
};
// end of namespace
}};
