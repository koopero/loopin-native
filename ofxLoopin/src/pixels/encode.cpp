#include "./main.hpp"
#include "lib/base64.h"

void ofxLoopin::pixels::Render::encode() {
  switch( format.getEnumValue() ) {
    case FORMAT_BASE64:
      encodeBinary();
      data = base64_encode( (const unsigned char *) data.c_str(), data.size() );
      return;
    break;

    case FORMAT_HEX:
      return encodeHex( 2 );
    break;

    case FORMAT_HEX2:
      return encodeHex( 1 );
    break;

    case FORMAT_FLOAT:
      return encodeNumeric( 1 );
    break;

    case FORMAT_PERCENT:
      return encodeNumeric( 100 );
    break;

    case FORMAT_DECIMAL:
      return encodeNumeric( 255 );
    break;
  }

}

void ofxLoopin::pixels::Render::encodeBinary() {
  data.resize( floats.size() );

  for ( int i = 0; i < floats.size(); i ++ ) {
    float valueF = floats[i];
    valueF = valueF > 1 ? 1 : valueF < 0 ? 0 : valueF;
    unsigned char valueC = valueF * 255;
    data[i] = valueC;
  }
}


void ofxLoopin::pixels::Render::encodeNumeric( float divider ) {
  int numChannels = channels.size();
  int channel = 0;
  stringstream result;

  for ( int i = 0; i < floats.size(); i ++ ) {
    float valueF = floats[i];
    valueF *= divider;
    if ( i ) result << ", ";

    result << valueF;
  }

  data = result.str();
}

void ofxLoopin::pixels::Render::encodeHex( int digits ) {
  static char charset[] = "0123456789abcef";
  data.resize( floats.size() * digits );

  for( int index = 0; index < floats.size(); index ++ ) {
    float valueF = floats[index];
    valueF = valueF > 1 ? 1 : valueF < 0 ? 0 : valueF;
    unsigned char valueC = valueF * 255;

    data[ index * digits ] = charset[(valueC >> 4) & 0xf];
    if ( digits == 2 )
      data[ index * digits + 1 ] = charset[valueC & 0xf];
  }
}
