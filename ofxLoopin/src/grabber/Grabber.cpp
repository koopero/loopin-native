#include "./Grabber.hpp"

ofJson ofxLoopin::grabber::GrabberList::infoGet() {
  ofJson result;

  result["devices"] = ofJson::array();

  ofVideoGrabber grabber;
  std::vector<ofVideoDevice> devices = grabber.listDevices();
  int ji = 0;
  for ( int i = 0; i < devices.size(); i ++ ) {
    result["devices"][ji]["deviceID"] = i;
    result["devices"][ji]["deviceName"] = devices[i].deviceName;
    result["devices"][ji]["hardwareName"] = devices[i].hardwareName;
    result["devices"][ji]["serialID"] = devices[i].serialID;
    result["devices"][ji]["available"] = devices[i].bAvailable;
    ji++;
  }

  return result;
}


void ofxLoopin::grabber::Grabber::refreshSetup() {
  if ( 
    _setupWidth != (int) width ||
    _setupHeight != (int) height ||
    _setupDeviceID != (int) deviceID
  ) {
    bool useTexture = true;

    grabber.setDeviceID( deviceID );
    grabber.setup( width, height, useTexture );

    if ( grabber.isInitialized() ) {
      ofxLoopinEvent event;
      event.type = "open";
      event.data["width"] = grabber.getWidth();
      event.data["height"] = grabber.getHeight();
      dispatch( event );
    }
    
    _setupWidth = width;
    _setupHeight = height;
    _setupDeviceID = deviceID;
  }
}

ofRectangle ofxLoopin::grabber::Grabber::getBounds() {

}

void ofxLoopin::grabber::Grabber::renderBuffer ( ofxLoopinBuffer * buffer ) {
  refreshSetup();
  grabber.update();

  ofTexture & texture = grabber.getTexture();
  buffer->setTexture( texture, true );
}
