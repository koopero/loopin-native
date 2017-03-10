#include "ofxLoopinPixels.h"
#include "ofxLoopinFile.h"
#include "lib/base64.h"


void ofxLoopinPixels::patchLocal( const Json::Value & value ) {

}

void ofxLoopinPixels::patchString( const string & value ) {
}

void ofxLoopinPixels::updateLocal( ) {

}

void ofxLoopinPixels::renderBuffer( ofxLoopinBuffer * buffer ) {
  outputPixels( buffer );
  renderPixels( buffer );
}

void ofxLoopinPixels::outputPixels( ofxLoopinBuffer * buffer ) {
  if ( !buffer || !buffer->isAllocated() ) {
    // TODO: Error
    return;
  }

  if ( output.getEnumValue() == OUTPUT_ONCE ) {
    output.setEnumValue( OUTPUT_NONE );
  } else if ( output.getEnumValue() == OUTPUT_NONE ) {
    return;
  }

  ofPixels pixels;
  ofFbo &fbo = buffer->getFbo();

  fbo.readToPixels( pixels );

  int numChannels = channels.size();
  int numPixels = pixels.getWidth() * pixels.getHeight();
  int dataSize = numPixels * numChannels;

  string data;
  data.resize( dataSize );

  int i = 0;

  for ( int y = 0; y < pixels.getHeight(); y++ )
  for ( int x = 0; x < pixels.getWidth(); x++ )
  {
    ofColor pixel = pixels.getColor( x, y );

    for ( int channelIndex = 0; channelIndex < numChannels; channelIndex ++ ) {
      switch ( channels[channelIndex] ) {
        case 'r': data[i++] = pixel.r;  break;
        case 'g': data[i++] = pixel.g;  break;
        case 'b': data[i++] = pixel.b;  break;
        case 'a': data[i++] = pixel.a;  break;
        case '1': data[i++] = 255; break;
        default: data[i++] = 0;
      }
    }
  }


  data = base64_encode( (const unsigned char *)data.c_str(), data.size() );
  ofxLoopinEvent event;
  event.type = "pixels";
  event.data["pixels"] = data;
  event.data["width"] = (int) pixels.getWidth();
  event.data["height"] = (int) pixels.getHeight();
  event.data["frame"] = renderingFrame.index;

  dispatch( event );
  pixels.clear();

}

ofRectangle ofxLoopinPixels::getBounds() {
  return ofRectangle( 0, 0, decodeInput().size() / channels.size(), 1 );
}


string ofxLoopinPixels::decodeInput() {
  switch( format.getEnumValue() ) {
    case FORMAT_BASE64:
      return base64_decode( pixels );
    break;

    case FORMAT_HEX:
      return decodeHex( pixels );
    break;
  }

  return "";
}

void ofxLoopinPixels::renderPixels( ofxLoopinBuffer * buffer ) {
  if ( !pixels.size() )
    return;

  string data = decodeInput();

  if ( input.getEnumValue() == INPUT_CHANGE && data == _lastPixels )
    return;

  if ( !buffer )
    buffer = getBuffer( true );

  buffer->defaultSize( getBounds() );

  if ( !buffer->begin() ) {
    // TODO: Error here
    return;
  }

  _lastPixels = data;


  int numChannels = channels.size();
  int numPixels = data.size() / numChannels;
  int bufferWidth = buffer->getWidth();
  int bufferHeight = buffer->getHeight();
  int x = 0;
  int y = 0;
  int i = 0;

  for ( int pixelIndex = 0; pixelIndex < numPixels; pixelIndex++ ) {

    ofColor pixel;
    for ( int channelIndex = 0; channelIndex < numChannels; channelIndex ++ ) {
      char channelKey = channels[channelIndex];
      unsigned char channelValue = data[i++];
      switch ( channelKey ) {
        case 'r': pixel.r = channelValue;     break;
        case 'g': pixel.g = channelValue;     break;
        case 'b': pixel.b = channelValue;     break;
      }
    }

    ofSetColor( pixel );
    ofDrawRectangle( x,y,1,1);

    x ++;
    if ( x >= bufferWidth ) {
      x = 0;
      y ++;
    }

    if ( y >= bufferHeight )
      break;
  }

  // cerr << "pixels::renderPixels " << data  << endl;
  buffer->end();
}

string ofxLoopinPixels::decodeHex( const string & input, int digits ) {
  string result;

  int i = 0;
  int value = 0;
  int digit = 0;
  for ( int inputIndex = 0; inputIndex < input.size(); ++inputIndex ) {
    value *= 0xF;
    char inputChar = input[inputIndex];
    bool valid = false;
    if ( inputChar >= '0' && inputChar <= '9' ) {
      value += inputChar - '0';
      valid = true;
    } else if ( inputChar >= 'a' && inputChar <= 'f' ) {
      value += inputChar - 'a' + 10;
      valid = true;
    } else if ( inputChar >= 'A' && inputChar <= 'F' ) {
      value += inputChar - 'A' + 10;
      valid = true;
    }

    if ( !valid )
      continue;

    digit ++;
    if ( digit == digits ) {
      digit = 0;

      result.append(1,(unsigned char) value);
      value = 0;
    }
  }

  return result;
}
