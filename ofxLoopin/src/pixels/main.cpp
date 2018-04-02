#include "./main.hpp"
#include "ofxLoopinFile.h"

ofxLoopinShader ofxLoopin::pixels::Render::shader = ofxLoopinShader(
// name
"solidRGBA",
// frag
#ifndef TARGET_OPENGLES:
"#version 150 \n\
uniform float red; \n\
uniform float green; \n\
uniform float blue; \n\
uniform float alpha; \n\
out vec4 OUT; \n\
void main() \n\
{ \n\
  OUT = vec4( red, green, blue, alpha ); \n\
} \n\
"
#else
"uniform float red; \n\
uniform float green; \n\
uniform float blue; \n\
uniform float alpha; \n\
void main() \n\
{ \n\
  gl_FragColor = vec4( red, green, blue, alpha ); \n\
} \n\
"
#endif
) ;


void ofxLoopin::pixels::Render::addSubControls() {
  // addSubControl("width", &width );
  // addSubControl("height", &height );
  addSubControl("box", &box );

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

void ofxLoopin::pixels::Render::patchLocal( const Json::Value & value ) {
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

void ofxLoopin::pixels::Render::patchString( const string & value ) {
  data = value;
  _isDirty = true;
}

void ofxLoopin::pixels::Render::updateLocal( ) {

}

void ofxLoopin::pixels::Render::renderBuffer( ofxLoopinBuffer * buffer ) {
  maybeOutputBuffer( buffer );

  bool inputIsFresh = decodeInput();

  if ( input.getEnumValue() == INPUT_CHANGE && !inputIsFresh )
    return;

  ofRectangle bounds = getBounds();

  if ( !buffer )
    buffer = getBuffer( true );

  bool resize = false;

  if ( resize ) {
    buffer->setSize( bounds.getWidth(), bounds.getHeight(), getFormat() );
  } else {
    buffer->defaultSize( bounds );
  }

  renderFloats( buffer );
}

GLint ofxLoopin::pixels::Render::getFormat() {

  bool hasAlpha = channels.find_first_of("a") != string::npos;

  #ifdef TARGET_OPENGLES
    return hasAlpha ? GL_RGBA : GL_RGB;
  #else
    bool isFloat;
    switch ( format.getEnumValue() ) {
      case FORMAT_HEX:
      case FORMAT_HEX2:
      case FORMAT_BASE64:
        isFloat = false;
      break;

      case FORMAT_FLOAT:
      case FORMAT_DECIMAL:
      case FORMAT_PERCENT:
        isFloat = true;
      break;
    }

    return isFloat ? GL_RGB32F_ARB :
      hasAlpha ? GL_RGBA8 : GL_RGB8;
  #endif
}

ofRectangle ofxLoopin::pixels::Render::getBounds() {
  int size = floats.size() / channels.size();
  int width = box.getAxis( 2 );
  int height = box.getAxis( 3 );

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

  return ofRectangle( box.getAxis(0), box.getAxis(1), width, height );
}

void ofxLoopin::pixels::Render::renderFloats( ofxLoopinBuffer * buffer ) {
  if ( !buffer->begin() ) {
    return;
  }
  
  shader.begin();
  glDisable( GL_CULL_FACE );
  ofDisableBlendMode( );
  ofDisableDepthTest();


  ofRectangle bounds = getBounds();

  int numChannels = channels.size();
  int numPixels = data.size() / numChannels;
  int bufferWidth = buffer->getWidth();
  int bufferHeight = buffer->getHeight();
  int x = bounds.getX();
  int y = bounds.getY();
  int i = 0;

  // cerr << "RenderFloats " << bounds << endl;
  // ofFill();
  for ( int pixelIndex = 0; pixelIndex < numPixels && i < floats.size(); pixelIndex++ ) {

    ofFloatColor pixel( 0,0,0,0.5 );

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

    shader.shader.setUniform1f( "red", (float) pixel.r / pixel.limit() );
    shader.shader.setUniform1f( "green", (float) pixel.g / pixel.limit() );
    shader.shader.setUniform1f( "blue", (float) pixel.b / pixel.limit() );
    shader.shader.setUniform1f( "alpha", (float) pixel.a / pixel.limit() );


    ofDrawRectangle( x,y,1,1);
    // ofDrawTriangle( x,y,x,y,x,y);

    cerr << "RenderFloats " << x << ", " << y << " " << pixel.b << endl;


    x ++;
    if ( x >= bounds.getWidth() + bounds.getX() ) {
      x = bounds.getX();
      y ++;
    }

    if ( y >= bounds.getHeight() + bounds.getY() )
      break;
  }

  shader.end();
  buffer->end();
}



void ofxLoopin::pixels::Render::maybeOutputBuffer( ofxLoopinBuffer * buffer ) {
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

void ofxLoopin::pixels::Render::bufferToFloats( ofxLoopinBuffer * buffer ) {
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

void ofxLoopin::pixels::Render::dispatchData() {
  ofxLoopinEvent event;
  ofRectangle bounds = getBounds();
  event.type = "pixels";
  event.data["width"] = readWidth ? readWidth : (int) bounds.getWidth();
  event.data["height"] = readHeight ? readHeight : (int) bounds.getHeight();
  event.data["format"] = format.getKey();
  event.data["frame"] = renderingFrame.index;
  event.data["data"] = data;
  event.data["channels"] = channels;
  
  dispatch( event );
}
