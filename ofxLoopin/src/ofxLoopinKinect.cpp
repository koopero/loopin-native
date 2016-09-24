#include "ofxLoopinKinect.h"

void ofxLoopinKinect::updateLocal() {
  if ( !kinect ) {
    kinect = new ofxKinect();
    kinect->init();
    kinect->setRegistration( true );
  }

  if ( !kinect ) {
    return;
  }

  bool shouldOpen = !kinect->isConnected();

  // Open if deviceId has changed
  shouldOpen = shouldOpen ||
    ( kinect->getDeviceId() != deviceId && deviceId != -1 );

  // Open if infrared has changed
  bool infrared = ofxLoopinKinect::infrared.getValue();
  shouldOpen = shouldOpen ||
    ( infrared != _modeInfrared );


  if ( shouldOpen ) {
    if ( kinect->isConnected() ) {
      kinect->close();
    }

    kinect->init( infrared, true, true );
    kinect->open();

    _modeInfrared = infrared;
  }


  kinect->update();

  if ( kinect->isConnected() && !status ) {
    status = true;

    ofxLoopinEvent event;
    event.type = "open";
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


void ofxLoopinKinect::render( ofxLoopinBuffer * buffer ) {
  if ( !kinect )
    return;

  if ( buffer == nullptr )
    buffer = getBuffer( true );

  Output outputType = ofxLoopinKinect::output.getEnumValue();

  renderBufferParams( buffer );

  if ( !buffer->begin() ) {
    // TODO: Error here
    return;
  }

  ofRectangle cropVideo = ofRectangle( 34, 39, 578, 434 );
  ofRectangle cropDepth = ofRectangle( 34, 39 + 434, 578, -434 );

  int width = buffer->getWidth();
  int height = buffer->getHeight();


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
      cerr << "alpha mode not implemented" << endl;
    break;
  }

  buffer->end();

};

void ofxLoopinKinect::drawVideo( const ofRectangle & crop, const ofRectangle & area ) {
  if ( !kinect->isFrameNewVideo() )
    return;

  ofTexture &texture = kinect->getTexture();

  texture.drawSubsection(
    area.x, area.y, area.width, area.height,
    crop.x, crop.y, crop.width, crop.height
  );
}

void ofxLoopinKinect::drawDepth( const ofRectangle & crop, const ofRectangle & area ) {
  ofxLoopinBuffer * depthBuffer = renderDepth();

  if ( depthBuffer == nullptr )
    return;

  ofTexture * depth = depthBuffer->getTexture();
  depth->setTextureMinMagFilter( GL_NEAREST, GL_NEAREST );
  depth->drawSubsection(
    area.x, area.y, area.width, area.height,
    crop.x, crop.y, crop.width, crop.height
  );
};

void ofxLoopinKinect::renderBufferParams( ofxLoopinBuffer * buffer ) {
  switch ( output.getEnumValue() ) {
    case OUTPUT_BOTH:
      buffer->setSize( 1280, 480, GL_RGB16 );
    break;

    case OUTPUT_VIDEO:
      if ( infrared ) {
        buffer->setSize( 640, 488, GL_RGB8 );
      } else {
        buffer->setSize( 640, 488, GL_RGB8 );
      }
    break;

    case OUTPUT_DEPTH:
      buffer->setSize( 1280, 480, GL_RGB16 );
    break;

    case OUTPUT_ALPHA:
      buffer->setSize( 1280, 480, GL_RGBA16 );
    break;
  }
};

void ofxLoopinKinect::readLocal( Json::Value & value ) {
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
