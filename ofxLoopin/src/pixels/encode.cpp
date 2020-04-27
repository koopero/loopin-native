#include "./Data.hpp"
#include "lib/base64.h"

void ofxLoopin::pixels::Data::encode() {
  switch( encoding.getEnumValue() ) {
    case ENCODING_BASE64:
      encodeBinary();
      data = base64_encode( (const unsigned char *) data.c_str(), data.size() );
      return;
    break;

    case ENCODING_HEX:
      return encodeHex( 2 );
    break;

    case ENCODING_HEX2:
      return encodeHex( 1 );
    break;

    case ENCODING_FLOAT:
      return encodeNumeric( 1 );
    break;

    case ENCODING_PERCENT:
      return encodeNumeric( 100 );
    break;

    case ENCODING_DECIMAL:
      return encodeNumeric( 255 );
    break;
  }

}

void ofxLoopin::pixels::Data::encodeBinary() {
  data.resize( floats.size() );

  for ( int i = 0; i < floats.size(); i ++ ) {
    float valueF = floats[i];
    valueF = valueF > 1 ? 1 : valueF < 0 ? 0 : valueF;
    unsigned char valueC = valueF * 255;
    data[i] = valueC;
  }
}


void ofxLoopin::pixels::Data::encodeNumeric( float divider ) {
  // std::cerr << "encodeNumeric " << divider << std::endl;
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

void ofxLoopin::pixels::Data::encodeHex( int digits ) {
  char charset[] = "0123456789abcdef";
  data.resize( floats.size() * digits );

  for( int index = 0; index < floats.size(); index ++ ) {
    float valueF = floats[index];
    valueF = valueF > 1 ? 1 : valueF < 0 ? 0 : valueF;
    uint8_t valueC = valueF * 255;

    data[ index * digits ] = charset[(valueC >> 4) & 0xf];
    if ( digits == 2 )
      data[ index * digits + 1 ] = charset[valueC & 0xf];
  }
}
