#include "./PS3Eye.hpp"

ofJson ofxLoopin::grabber::PS3EyeList::infoGet() {
  ofJson result;

  result["devices"] = ofJson::array();

  ofxPS3EyeGrabber grabber;
  std::vector<ofVideoDevice> devices = grabber.listDevices();
  int ji = 0;
  for ( int i = 0; i < devices.size(); i ++ ) {
    result["devices"][ji]["deviceID"] = i;
    result["devices"][ji]["deviceName"] = devices[i].deviceName;
    result["devices"][ji]["available"] = devices[i].bAvailable;
    ji++;
  }

  return result;
}

bool ofxLoopin::grabber::PS3Eye::renderSetup() {

  if ( !_init ) {
    cerr << "init ps3eye" << endl;
    grabber.setGrabber(std::make_shared<ofxPS3EyeGrabber>());
    grabber.setup( 320, 250 );

    grabber.setDesiredFrameRate(180);

    
    // These are examples of ofxPS3EyeGrabber-specific paramaters.
    // These must be set after the grabber is set up.
     grabber.getGrabber<ofxPS3EyeGrabber>()->setAutogain(true);
     grabber.getGrabber<ofxPS3EyeGrabber>()->setAutoWhiteBalance(true);
    _init = true;
  }


  return true;
}

void ofxLoopin::grabber::PS3Eye::renderBuffer ( ofxLoopin::base::Buffer * buffer ) {
  if ( !renderSetup() )
    return;

  
  refreshSetup();
  grabber.update();

  buffer->setSize( 640, 480 );
  if ( !buffer->begin() )
    return;




  cerr << "render ps3eye" << endl;
  ofSetColor(255);
  grabber.draw( 0, 0, 120, 120 );
  ofDrawRectangle( 10, 10, 60, 60 );


  std::stringstream ss;

  ss << " App FPS: " << ofGetFrameRate() << std::endl;
  // ss << " Cam FPS: " << grabber.getGrabber<ofxPS3EyeGrabber>()->getFPS() << std::endl;
  // ss << "Real FPS: " << grabber.getGrabber<ofxPS3EyeGrabber>()->getActualFPS() << std::endl;
  ss << "      id: 0x" << ofToHex(grabber.getGrabber<ofxPS3EyeGrabber>()->getDeviceId());

  ofDrawBitmapStringHighlight(ss.str(), ofPoint(10, 15));

  buffer->end();


  // ofTexture & texture = grabber.getTexture();
  // buffer->setTexture( texture, true );
}



ofRectangle ofxLoopin::grabber::PS3Eye::getBounds() {
  if ( _settings.half ) 
    return ofRectangle( 0, 0, 320, 240 );

  return ofRectangle( 0, 0, 640, 480 );
}

// ofTexture * ofxLoopin::grabber::PS3Eye::textureToRender() {
//   grabber.update();
//   return grabber.getTexturePtr();
// }


void ofxLoopin::grabber::PS3Eye::controlsToSettings( PS3EyeSettings & settings ) {

}


void ofxLoopin::grabber::PS3Eye::refreshSetup() {
  PS3EyeSettings next;
  controlsToSettings( next );



  // if ( 
  //   _setupWidth != (int) width ||
  //   _setupHeight != (int) height ||
  //   _setupDeviceID != (int) deviceID
  // ) {
  //   ofxLoopin::control::Event event;
  //   bool useTexture = true;

  //   event.type = "captureStart";
  //   dispatch( event );

  //   grabber.setDeviceID( deviceID );
  //   grabber.setup( width, height, useTexture );

  //   event.type = "captureEnd";
  //   dispatch( event );

  //   if ( grabber.isInitialized() ) {
  //     event.type = "open";
  //     event.data["width"] = grabber.getWidth();
  //     event.data["height"] = grabber.getHeight();
  //     dispatch( event );
  //   }
    
  //   _setupWidth = width;
  //   _setupHeight = height;
  //   _setupDeviceID = deviceID;
  // }
}

// ofRectangle ofxLoopin::grabber::PS3Eye::getBounds() {
//   int _width = grabber.getWidth();
//   int _height = grabber.getHeight();

//   if ( !_width || !_height ) {
//     _width = width;
//     _height = height;
//   }

//   return ofRectangle( 0, 0, _width, _height );
// }

// void ofxLoopin::grabber::PS3Eye::renderBuffer ( ofxLoopin::base::Buffer * buffer ) {
//   refreshSetup();
//   grabber.update();

//   ofTexture & texture = grabber.getTexture();
//   buffer->setTexture( texture, true );
// }
