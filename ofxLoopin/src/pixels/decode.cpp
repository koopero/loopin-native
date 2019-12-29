#include "./Data.hpp"
#include "lib/base64.h"


bool ofxLoopin::pixels::Data::dataToFloats() {

  if ( !_isDirty )
    return false;


  switch( encoding.getEnumValue() ) {
    case ENCODING_BASE64:
      decodeBinary( base64_decode( data ) );
    break;

    case ENCODING_HEX:
      decodeHex();
    break;

    case ENCODING_HEX2:
      decodeHex( 1 );
    break;

    case ENCODING_FLOAT:
      decodeNumeric( 1 );
    break;

    case ENCODING_PERCENT:
      decodeNumeric( 100 );
    break;

    case ENCODING_DECIMAL:
      decodeNumeric( 255 );
    break;
  }

  _isDirty = false;

  return true;
}



void ofxLoopin::pixels::Data::decodeHex( int digits ) {
  floats.resize(0);

  int i = 0;
  int valueI = 0;
  int digit = 0;
  float divider = pow(16, digits ) - 1;
  for ( int inputIndex = 0; inputIndex < data.size(); ++inputIndex ) {
    valueI *= 16;
    char inputChar = data[inputIndex];
    bool valid = false;

    if ( inputChar >= '0' && inputChar <= '9' ) {
      valueI += inputChar - '0';
      valid = true;
    } else if ( inputChar >= 'a' && inputChar <= 'f' ) {
      valueI += inputChar - 'a' + 10;
      valid = true;
    } else if ( inputChar >= 'A' && inputChar <= 'F' ) {
      valueI += inputChar - 'A' + 10;
      valid = true;
    }

    if ( !valid )
      continue;

    digit ++;

    if ( digit == digits ) {
      digit = 0;
      float valueF = (float) valueI / (float) divider;
      floats.push_back( valueF );
      valueI = 0;
    }
  }
}

void ofxLoopin::pixels::Data::decodeBinary( const string &data ) {
  floats.resize( data.size() );
  for ( int index = 0; index < data.size(); index ++ ) {
    unsigned char valueC = data[ index ];
    float valueF = (float) valueC / 255.0;
    floats[index] = valueF;
  }
}

void ofxLoopin::pixels::Data::decodeNumeric( float divider ) {
  floats.resize( 0 );

  size_t index = 0;
  size_t begin = 0;
  size_t end = 0;

  do {
    begin = data.find_first_of( "0123456789-", end );

    if ( begin == string::npos )
      break;

    end = data.find_first_not_of( "0123456789.e-", begin + 1 );

    if ( end == string::npos )
      end = data.size();

    string seg = data.substr( begin, end - begin );
    float value = stof( seg );
    value /= divider;
    floats.push_back( value );
  } while ( end < data.size() - 1 );


}
