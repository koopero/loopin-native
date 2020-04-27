#include "./Data.hpp"

GLint ofxLoopin::pixels::Data::getGLFormat() {

  bool hasAlpha = channels.find_first_of("a") != string::npos;

  #ifdef TARGET_OPENGLES
    return hasAlpha ? GL_RGBA : GL_RGB;
  #else
    bool isFloat;
    switch ( encoding.getEnumValue() ) {
      case ENCODING_HEX:
      case ENCODING_HEX2:
      case ENCODING_BASE64:
        isFloat = false;
      break;

      case ENCODING_FLOAT:
      case ENCODING_DECIMAL:
      case ENCODING_PERCENT:
        isFloat = true;
      break;
    }

    return isFloat ? GL_RGBA32F_ARB :
      hasAlpha ? GL_RGBA8 : GL_RGB8;
  #endif
}

void ofxLoopin::pixels::Data::pixelsToFloats( const ofFloatPixels & pixels ) {
  // readWidth = pixels.getWidth();
  // readHeight = pixels.getHeight();

  int numChannels = channels.size();
  int numPixels = pixels.getWidth() * pixels.getHeight();
  int dataSize = numPixels * numChannels;

  floats.resize( dataSize );

  int i = 0;

  for ( int y = 0; y < pixels.getHeight(); y++ )
  for ( int x = 0; x < pixels.getWidth(); x++ )
  {
    ofFloatColor pixel = pixels.getColor( x, y );

    for ( int channelIndex = 0; channelIndex < numChannels; channelIndex ++ ) {
      switch ( channels[channelIndex] ) {
        case 'r': floats[i++] = pixel.r;  break;
        case 'g': floats[i++] = pixel.g;  break;
        case 'b': floats[i++] = pixel.b;  break;
        case 'a': floats[i++] = pixel.a;  break;
        case 'h': floats[i++] = pixel.getHue();  break;

        case '1': floats[i++] = 1.0; break;
        default: floats[i++] = 0;
      }
    }
  }
}

