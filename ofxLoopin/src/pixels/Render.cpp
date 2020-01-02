#include "./Render.hpp"

ofxLoopin::shader::Shader ofxLoopin::pixels::Render::shader = ofxLoopin::shader::Shader(
// name
"solidRGBA",
// frag
#ifndef TARGET_OPENGLES
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



void ofxLoopin::pixels::Render::renderBuffer( ofxLoopin::base::Buffer * buffer ) {
  maybeOutputBuffer( buffer );

  bool inputIsFresh = dataToFloats();



  if ( !input.isEnabledOnce( inputIsFresh ) )
    return;

  // cerr << "renderBuffer " << inputIsFresh << endl;


  ofRectangle bounds = getBounds();

  if ( !buffer )
    buffer = getBuffer( true );

  if ( replace ) {
    buffer->setSize( bounds.getWidth(), bounds.getHeight(), getGLFormat() );
  } else {
    buffer->defaultSize( bounds );
  }

  renderFloats( buffer );
}

void ofxLoopin::pixels::Render::renderFloats( ofxLoopin::base::Buffer * buffer ) {
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

    ofFloatColor pixel( 0,0,0,1.0 );

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
    // cerr << "RenderFloats " << x << ", " << y << " " << pixel.b << endl;


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




void ofxLoopin::pixels::Render::maybeOutputBuffer( ofxLoopin::base::Buffer * buffer ) {
  if ( !buffer || !buffer->isAllocated() ) {
    // TODO: Error
    std::cerr << "bufferFalout" << std::endl;
    return;
  }

  bool outputIsFresh = true;

  if ( !output.isEnabledOnce( outputIsFresh ) )
    return;
    
  ofFbo &fbo = buffer->getFbo();
  fbo.readToPixels( pixels );
  readWidth = pixels.getWidth();
  readHeight = pixels.getHeight();
  pixelsToFloats();
  encode();
  dispatchData();
}


void ofxLoopin::pixels::Render::dispatchData() {
  ofxLoopin::control::Event event;
  ofRectangle bounds = getBounds();
  event.type = "pixels";
  event.data["width"] = readWidth ? readWidth : (int) bounds.getWidth();
  event.data["height"] = readHeight ? readHeight : (int) bounds.getHeight();
  event.data["encoding"] = encoding.getKey();
  event.data["frame"] = renderingFrame.index;
  event.data["data"] = data;
  event.data["channels"] = channels;
  
  dispatch( event );
}


