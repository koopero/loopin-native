#include "./Kinect.hpp"
#include "ofGraphics.h"


ofxLoopin::shader::Shader ofxLoopin::kinect::Kinect::_bothShader = ofxLoopin::shader::Shader(
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

void ofxLoopin::kinect::Kinect::addSubControls() {

  addSubControl( "enable", &enable );


  addSubControl( "deviceID", new ofxLoopin::control::Value( &deviceId ) );

  addSubControl( "tilt", &tilt );
  addSubControl( "infrared", &infrared );
  addSubControl( "registration", &registration );


  led.enumAddOption("default", ofxKinect::LedMode::LED_DEFAULT );
  led.enumAddOption("off", ofxKinect::LedMode::LED_OFF );
  led.enumAddOption("green", ofxKinect::LedMode::LED_GREEN );
  led.enumAddOption("red", ofxKinect::LedMode::LED_RED );
  led.enumAddOption("yellow", ofxKinect::LedMode::LED_YELLOW );
  led.enumAddOption("blinkGreen", ofxKinect::LedMode::LED_BLINK_GREEN );
  led.enumAddOption("blinkYellowRed", ofxKinect::LedMode::LED_BLINK_YELLOW_RED );

  addSubControl( "led", &led );

  output.enumAddOption("both", OUTPUT_BOTH );
  output.enumAddOption("video", OUTPUT_VIDEO );
  output.enumAddOption("depth", OUTPUT_DEPTH );
  output.enumAddOption("alpha", OUTPUT_ALPHA );

  addSubControl( "output", &output );
};

void ofxLoopin::kinect::Kinect::updateLocal() {
  if ( !enable.isEnabled() ) {
    closeKinect();
    return;
  }


  if ( !kinect ) {
    kinect = new ofxKinect();
    kinect->init();
  }

  if ( !kinect ) {
    return;
  }



  bool shouldOpen = !kinect->isConnected();
  ofxLoopin::control::Event event;
  // Open if deviceId has changed
  shouldOpen = shouldOpen ||
    ( kinect->getDeviceId() != deviceId && deviceId != -1 ); 

  // Open if infrared has changed
  bool infrared = ofxLoopin::kinect::Kinect::infrared.getValue();
  shouldOpen = shouldOpen ||
    ( infrared != _modeInfrared );

  bool registration = ofxLoopin::kinect::Kinect::registration.getValue();
  shouldOpen = shouldOpen ||
    ( registration != _modeRegistration );

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
      kinect->setRegistration( (bool) registration );

      cerr << "***** Kinect opening " << deviceId << endl;
      kinect->open( deviceId );

      event.type = "captureEnd";
      if ( root ) dispatch( event );

      _modeInfrared = infrared;
      _modeRegistration = registration;
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

    ofxLoopin::control::Event event;
    event.type = "close";
    dispatch( event );
  }

  if ( !kinect->isConnected() )
    return;

  updateLed();
  updateTilt();


};

void ofxLoopin::kinect::Kinect::closeKinect() {
  if ( kinect && kinect->isConnected() ) {
    kinect->clear();
  }
}

ofxLoopin::base::Buffer * ofxLoopin::kinect::Kinect::renderDepth() {
  if ( !kinect )
    return NULL;

  ofTexture &depth = kinect->getDepthTexture();

  // ofxLoopin::shader::Shader * shader = ofxLoopin::render::Render::shader.getPointer();
  // shader->begin();

  ofxLoopin::base::Buffer * depthBuffer = getBuffer( key + ":depth", true );
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


void ofxLoopin::kinect::Kinect::renderBuffer( ofxLoopin::base::Buffer * buffer ) {
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

  Output outputType = ofxLoopin::kinect::Kinect::output.getEnumValue();
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
  enable.resetOnce();
};

void ofxLoopin::kinect::Kinect::drawVideo( const ofRectangle & crop, const ofRectangle & area ) {
  if ( !kinect->isFrameNewVideo() )
    return;

  ofSetupScreen();

  ofTexture &texture = kinect->getTexture();

  texture.drawSubsection(
    area.x, area.y, area.width, area.height,
    crop.x, crop.y, crop.width, crop.height
  );
}

void ofxLoopin::kinect::Kinect::drawDepth( const ofRectangle & crop, const ofRectangle & area ) {
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

void ofxLoopin::kinect::Kinect::drawBoth( const ofRectangle & area ) {
  ofShader & shader = _bothShader.shader;
  ofSetupScreen();

  _bothShader.begin();

  ofTexture &videoTexture = kinect->getTexture();
  if ( videoTexture.isAllocated() ) {
    videoTexture.bind( 2 );
    shader.setUniformTexture( "videoSampler", videoTexture, 2 );
  }

  ofxLoopin::base::Buffer * depthBuffer = renderDepth();
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

void ofxLoopin::kinect::Kinect::renderBufferParams( ofxLoopin::base::Buffer * buffer ) {
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

void ofxLoopin::kinect::Kinect::readLocal( ofJson & value ) {
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
