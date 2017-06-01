#include "ofxLoopinPixels.h"
#include "ofxLoopinFile.h"


void ofxLoopinPixels::patchLocal( const Json::Value & value ) {
  if (
   value.isObject() && (
     value.isMember("data")
     || value.isMember("format")
     || value.isMember("channels")
   )
  ) {
    _isDirty = true;
  }
}

void ofxLoopinPixels::patchString( const string & value ) {
  data = value;
  _isDirty = true;
}

void ofxLoopinPixels::updateLocal( ) {

}

void ofxLoopinPixels::renderBuffer( ofxLoopinBuffer * buffer ) {
  maybeOutputBuffer( buffer );

  bool inputIsFresh = decodeInput();

  if ( input.getEnumValue() == INPUT_CHANGE && !inputIsFresh )
    return;

  if ( !buffer )
    buffer = getBuffer( true );

  buffer->defaultSize( getBounds() );

  renderFloats( buffer );
}

ofRectangle ofxLoopinPixels::getBounds() {
  int size = floats.size() / channels.size();
  int width = ofxLoopinPixels::width;
  int height = ofxLoopinPixels::height;

  if ( width < 1 && height < 1 ) {
    width = size;
    height = 1;
  } else if ( width ) {
    if ( height < 1 )
      height = ceil( (float) size / width );
  } else if ( height ) {
    width = 1;
  }

  if ( width < 1 )
    width = 0;

  if ( height < 1 )
    height = 0;

  return ofRectangle( 0, 0, width, height );
}

void ofxLoopinPixels::renderFloats( ofxLoopinBuffer * buffer ) {
  if ( !buffer->begin() ) {
    return;
  }

  ofxLoopinShader * shader = ofxLoopinPixels::shader.getPointer( true );
  if ( !shader ) { dispatch("shaderFault"); return; }



  glDisable( GL_CULL_FACE );
  ofDisableBlendMode();
  ofDisableDepthTest();
  // ofLoadIdentityMatrix();
  // ofViewport();
  shader->begin();


  int numChannels = channels.size();
  int numPixels = data.size() / numChannels;
  int bufferWidth = buffer->getWidth();
  int bufferHeight = buffer->getHeight();
  int x = 0;
  int y = 0;
  int i = 0;
  ofFill();
  for ( int pixelIndex = 0; pixelIndex < numPixels && i < floats.size(); pixelIndex++ ) {

    ofFloatColor pixel( 0,0,0,1);

    for ( int channelIndex = 0; channelIndex < numChannels && i < floats.size(); channelIndex ++ ) {
      char channelKey = channels[channelIndex];
      float channelValue = floats[i++] * pixel.limit();
      switch ( channelKey ) {
        case 'r': pixel.r = channelValue;     break;
        case 'g': pixel.g = channelValue;     break;
        case 'b': pixel.b = channelValue;     break;
        case 'a': pixel.a = channelValue;     break;

        // Temp until real HSV support
        case 'l':
        case 'v':
          pixel.r = channelValue;
          pixel.g = channelValue;
          pixel.b = channelValue;
        break;
      }
    }

    shader->shader.setUniform1f( "red", (float) pixel.r / pixel.limit() );
    shader->shader.setUniform1f( "green", (float) pixel.g / pixel.limit() );
    shader->shader.setUniform1f( "blue", (float) pixel.b / pixel.limit() );
    shader->shader.setUniform1f( "alpha", (float) pixel.a / pixel.limit() );


    ofDrawRectangle( x,y,1,1);
    // ofDrawTriangle( x,y,x,y,x,y);

    x ++;
    if ( x >= bufferWidth ) {
      x = 0;
      y ++;
    }

    if ( y >= bufferHeight )
      break;
  }

  shader->end();
  buffer->end();
}



void ofxLoopinPixels::maybeOutputBuffer( ofxLoopinBuffer * buffer ) {
  if ( !buffer || !buffer->isAllocated() ) {
    // TODO: Error
    return;
  }

  if ( output.getEnumValue() == OUTPUT_NONE ) {
    return;
  } else if ( output.getEnumValue() == OUTPUT_ONCE ) {
    output.setEnumValue( OUTPUT_NONE );
  }

  bufferToFloats( buffer );
  encode();
  dispatchData();
}

void ofxLoopinPixels::bufferToFloats( ofxLoopinBuffer * buffer ) {
  #ifndef TARGET_OPENGLES
    ofFloatPixels pixels;
  #else
    ofPixels pixels;
  #endif

  ofFbo &fbo = buffer->getFbo();
  fbo.readToPixels( pixels );

  readWidth = pixels.getWidth();
  readHeight = pixels.getHeight();

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

void ofxLoopinPixels::dispatchData() {
  ofxLoopinEvent event;
  ofRectangle bounds = getBounds();
  event.type = "pixels";
  event.data["width"] = readWidth ? readWidth : (int) bounds.getWidth();
  event.data["height"] = readHeight ? readHeight : (int) bounds.getHeight();
  event.data["format"] = format.getKey();
  event.data["frame"] = renderingFrame.index;
  event.data["data"] = data;

  dispatch( event );
}
