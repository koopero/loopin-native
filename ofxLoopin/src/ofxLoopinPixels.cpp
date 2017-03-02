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
  renderPixels( buffer, pixels );
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
  for ( int pixelIndex = 0; pixelIndex < numPixels; pixelIndex ++ ) {
    ofColor pixel = pixels.getColor( pixelIndex * pixels.getNumChannels() );

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
  event.data["frame"] = renderingFrame.index;
  event.data["width"] = buffer->getWidth();
  event.data["height"] = buffer->getHeight();


  dispatch( event );
}

ofRectangle ofxLoopinPixels::getBounds() {
  return ofRectangle( 0, 0, decodeInput().size() / channels.size(), 1 );
}


string ofxLoopinPixels::decodeInput() {
  switch( format.getEnumValue() ) {
    case FORMAT_BASE64:
      return base64_decode( pixels );
    break;
  }

  return "";
}

void ofxLoopinPixels::renderPixels( ofxLoopinBuffer * buffer, const string & pixels ) {
  if ( !pixels.size() )
    return;

  if ( input.getEnumValue() == INPUT_CHANGE && pixels == _lastPixels )
    return;

  if ( !buffer )
    buffer = getBuffer( true );

  buffer->defaultSize( getBounds() );

  if ( !buffer->begin() ) {
    // TODO: Error here
    return;
  }

  _lastPixels = pixels;

  string data;
  switch( format.getEnumValue() ) {
    case FORMAT_BASE64:
      data = base64_decode( pixels );
    break;
  }

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
