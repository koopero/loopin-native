#include "ofxLoopinKinect.h"
#include "ofGraphics.h"


ofxLoopinShader ofxLoopinKinect::_bothShader = ofxLoopinShader(
#ifndef TARGET_OPENGLES
// name
"kinectBoth",
// vert
"\#version 150\n\
uniform mat4 modelViewProjectionMatrix;\n\
uniform mat4 srcMatrix;\n\
uniform sampler2D srcSampler;\n\
in vec4 position;\n\
in vec2 texcoord;\n\
in vec4 color;\n\
out vec2 srcCoord;\n\
// out vec4 vertColour;\n\
void main()\n\
{\n\
    srcCoord = texcoord.xy;\n\
    // srcCoord *= vec2( 640, 480 );\n\
    // srcCoord *= vec2( 640, 480 );\n\
    // srcCoord = (srcMatrix*vec4(srcCoord.x,srcCoord.y,0,1)).xy;\n\
    // vertColour = color;\n\
    // vertColour = vec4(1,1,1,1);\n\
    // gl_Position = modelViewProjectionMatrix * position;\n\
    gl_Position = position;\n\
}\n\
",
// frag
"#version 150 \n\
uniform sampler2D depthSampler; \n\
uniform sampler2D videoSampler; \n\
in vec2 srcCoord; \n\
out vec4 OUT; \n\
void main() \n\
{ \n\
  OUT.rgb = texture(videoSampler, srcCoord).rgb; \n\
  OUT.a   = texture(depthSampler, srcCoord).g; \n\
  // OUT.rg  = srcCoord; \n\
  // OUT.r  = 1.0 - OUT.r; \n\
  // OUT.a   = 1.0; \n\
} \n\
"
#else
#warning "Kinect on OpenGL ES not supported"
#endif
);

void ofxLoopinKinect::addSubControls() {

  addSubControl( "tilt", &tilt );
  addSubControl( "infrared", &infrared );

  led.setEnumKey("default", ofxKinect::LedMode::LED_DEFAULT );
  led.setEnumKey("off", ofxKinect::LedMode::LED_OFF );
  led.setEnumKey("green", ofxKinect::LedMode::LED_GREEN );
  led.setEnumKey("red", ofxKinect::LedMode::LED_RED );
  led.setEnumKey("yellow", ofxKinect::LedMode::LED_YELLOW );
  led.setEnumKey("blinkGreen", ofxKinect::LedMode::LED_BLINK_GREEN );
  led.setEnumKey("blinkYellowRed", ofxKinect::LedMode::LED_BLINK_YELLOW_RED );

  addSubControl( "led", &led );

  output.setEnumKey("both", OUTPUT_BOTH );
  output.setEnumKey("video", OUTPUT_VIDEO );
  output.setEnumKey("depth", OUTPUT_DEPTH );
  output.setEnumKey("alpha", OUTPUT_ALPHA );

  addSubControl( "output", &output );
};

void ofxLoopinKinect::updateLocal() {
  if ( !kinect ) {
    kinect = new ofxKinect();
    kinect->init();
    kinect->setRegistration( false );
  }

  if ( !kinect ) {
    return;
  }

  bool shouldOpen = !kinect->isConnected();
  ofxLoopinEvent event;
  // Open if deviceId has changed
  shouldOpen = shouldOpen ||
    ( kinect->getDeviceId() != deviceId && deviceId != -1 );

  // Open if infrared has changed
  bool infrared = ofxLoopinKinect::infrared.getValue();
  shouldOpen = shouldOpen ||
    ( infrared != _modeInfrared );

  float now = ofGetElapsedTimef();

  if ( shouldOpen ) {
    if ( now > _triedOpening + 10 ) {
      _triedOpening = now;
      if ( kinect->isConnected() ) {
        kinect->close();
      }


      event.type = "captureStart";
      if ( root ) dispatch( event );

      kinect->init( infrared, true, true );
      kinect->open();

      event.type = "captureEnd";
      if ( root ) dispatch( event );

      _modeInfrared = infrared;
    }
  }


  kinect->update();

  if ( kinect->isConnected() && !status ) {
    status = true;

    event.type = "open";
    readLocal( event.data );
    dispatch( event );
  } else if ( !kinect->isConnected() && status ) {
    status = false;

    ofxLoopinEvent event;
    event.type = "close";
    dispatch( event );
  }

  if ( !kinect->isConnected() )
    return;

  updateLed();
  updateTilt();

};

ofxLoopinBuffer * ofxLoopinKinect::renderDepth() {
  if ( !kinect )
    return NULL;

  ofTexture &depth = kinect->getDepthTexture();

  // ofxLoopinShader * shader = ofxLoopinRender::shader.getPointer();
  // shader->begin();

  ofxLoopinBuffer * depthBuffer = getBuffer( key + ":depth", true );
  depthBuffer->setSize( 640, 480 );

  depthBuffer->begin();
  // depth.setTextureMinMagFilter( GL_NEAREST, GL_NEAREST );
  depth.draw( 0, 0, 640, 480 );
  depthBuffer->end();

  // for ( int i = 0; i < fill; i ++ ) {
  //   depthBuffer->begin();
  //   depthBuffer->getTexture()->draw( 0, 0, 640, 480 );
  //   depthBuffer->end();
  // }
  //
  // shader->end();

  return depthBuffer;
}


void ofxLoopinKinect::renderBuffer( ofxLoopinBuffer * buffer ) {
  if ( !kinect || !kinect->isConnected() )
    return;

  if ( !buffer ) {
    buffer = getBuffer( true );
  }

  renderBufferParams( buffer );

  if ( !buffer->begin() ) {
    // TODO: Error here
    return;
  }



  // ofRectangle cropVideo = ofRectangle( 34, 39, 578, 434 );
  // ofRectangle cropDepth = ofRectangle( 34, 39 + 434, 578, -434 );
  ofRectangle cropVideo = ofRectangle( 0, 0, 640, 480 );
  ofRectangle cropDepth = ofRectangle( 0, 0, 640, 480 );

  int width = buffer->getWidth();
  int height = buffer->getHeight();

  Output outputType = ofxLoopinKinect::output.getEnumValue();
  switch ( outputType ) {
    case OUTPUT_BOTH:
      drawVideo( cropVideo, ofRectangle( 0, 0, width / 2, height ) );
      drawDepth( cropDepth, ofRectangle( width / 2, 0, width / 2, height ) );
    break;

    case OUTPUT_VIDEO:
      drawVideo( cropVideo, ofRectangle( 0, 0, width, height ) );
    break;

    case OUTPUT_DEPTH:
      drawDepth( cropDepth, ofRectangle( 0, 0, width, height ) );
    break;

    case OUTPUT_ALPHA:
      drawBoth( ofRectangle( 0, 0, width, height ) );
    break;
  }

  buffer->end();

};

void ofxLoopinKinect::drawVideo( const ofRectangle & crop, const ofRectangle & area ) {
  if ( !kinect->isFrameNewVideo() )
    return;

  ofSetupScreen();

  ofTexture &texture = kinect->getTexture();

  texture.drawSubsection(
    area.x, area.y, area.width, area.height,
    crop.x, crop.y, crop.width, crop.height
  );
}

void ofxLoopinKinect::drawDepth( const ofRectangle & crop, const ofRectangle & area ) {
  if ( !kinect->isFrameNewDepth() )
    return;


  ofSetupScreen();
  ofTexture &depthTexture = kinect->getDepthTexture();
  depthTexture.setTextureWrap( GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE );
  depthTexture.setTextureMinMagFilter( GL_NEAREST, GL_NEAREST );

  depthTexture.drawSubsection(
    area.x, area.y, area.width, area.height,
    crop.x, crop.y, crop.width, crop.height
  );
};

void ofxLoopinKinect::drawBoth( const ofRectangle & area ) {
  ofShader & shader = _bothShader.shader;
  ofSetupScreen();

  _bothShader.begin();

  ofTexture &videoTexture = kinect->getTexture();
  if ( videoTexture.isAllocated() ) {
    videoTexture.bind( 2 );
    shader.setUniformTexture( "videoSampler", videoTexture, 2 );
  }

  ofxLoopinBuffer * depthBuffer = renderDepth();
  ofTexture &depthTexture = kinect->getDepthTexture();
  if ( depthTexture.isAllocated() ) {
    depthTexture.setTextureWrap( GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE );
    depthTexture.setTextureMinMagFilter( GL_NEAREST, GL_NEAREST );
    depthTexture.bind( 1 );

    shader.setUniformTexture( "depthSampler", depthTexture, 1 );
  }

  ofClear( 0, 0, 0, 0 );
  ofDisableBlendMode();
  videoTexture.draw( -1, -1, 2, 2 );

  _bothShader.end();
  videoTexture.unbind();
  depthTexture.unbind();
};

void ofxLoopinKinect::renderBufferParams( ofxLoopinBuffer * buffer ) {
  #ifndef TARGET_OPENGLES
    // Use some 16-bit buffers for real GL
    GLint formatRGBDeep  = GL_RGB16;
    GLint formatRGB      = GL_RGB8;
    GLint formatRGBADeep = GL_RGBA16;
  #else
    // Standard formats for ES
    GLint formatRGBDeep  = GL_RGB;
    GLint formatRGB      = GL_RGB;
    GLint formatRGBADeep = GL_RGBA;
  #endif

  switch ( output.getEnumValue() ) {
    case OUTPUT_BOTH:
      buffer->setSize( 1280, 480, formatRGBDeep );
    break;

    case OUTPUT_VIDEO:
      if ( infrared ) {
        buffer->setSize( 640, 488, formatRGB );
      } else {
        buffer->setSize( 640, 480, formatRGB );
      }
    break;

    case OUTPUT_DEPTH:
      buffer->setSize( 640, 480, formatRGBDeep );
    break;

    case OUTPUT_ALPHA:
      buffer->setSize( 640, 480, formatRGBADeep );
    break;
  }

};

void ofxLoopinKinect::readLocal( ofJson & value ) {
  if ( kinect ) {
    value["open"]   = kinect->isConnected();
    value["id"]     = kinect->getDeviceId();
    value["serial"] = kinect->getSerial();
    value["near"]   = kinect->getNearClipping();
    value["far"]    = kinect->getFarClipping();
  } else {
    value["open"]   = false;
  }
}
