#include "./PS3Eye.hpp"

ofJson ofxLoopin::grabber::PS3EyeList::infoGet() {
  ofJson result;

  result["devices"] = ofJson::array();

  ofxPS3EyeGrabber grabber;
  std::vector<ofVideoDevice> devices = grabber.listDevices();
  int ji = 0;
  for ( int i = 0; i < devices.size(); i ++ ) {
    result["devices"][ji]["deviceID"] = devices[i].id;
    result["devices"][ji]["deviceName"] = devices[i].deviceName;
    result["devices"][ji]["available"] = devices[i].bAvailable;
    ji++;
  }

  return result;
}

bool ofxLoopin::grabber::PS3Eye::renderSetup() {

  if ( !_init ) {
    // grabber.setGrabber(std::make_shared<ofxPS3EyeGrabber>());
    // grabber.setup( 320, 240 );
    // grabber.setDesiredFrameRate(180);

    // These are examples of ofxPS3EyeGrabber-specific paramaters.
    // These must be set after the grabber is set up.
    //  grabber.getGrabber<ofxPS3EyeGrabber>()->setAutogain(true);
    //  grabber.getGrabber<ofxPS3EyeGrabber>()->setAutoWhiteBalance(true);
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
  grabber.draw( 0, 0, 640, 480 );

  std::stringstream ss;

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

uint8_t ofxLoopin::grabber::PS3Eye::settingsRange( float val, uint8_t max ) {
  val = round( val * max );
  val = val < 0 ? 0 : val > max ? max : val;
  return val;
}

void ofxLoopin::grabber::PS3Eye::controlsToSettings( PS3EyeSettings & settings ) {
  settings.deviceID = deviceID;
  settings.rate = rate;

  settings.half = half;
  settings.autoGain = autoGain;
  settings.autoWhiteBalance = autoWhiteBalance;
  settings.flipHorizontal = flipHorizontal;
  settings.flipVertical = flipVertical;

  settings.gain = settingsRange( gain, 63 );
  settings.exposure = settingsRange( exposure );
  settings.sharpness = settingsRange( sharpness, 63 );
  settings.contrast = settingsRange( contrast, 63 );
  settings.brightness = settingsRange( brightness, 63 );
  settings.hue = settingsRange( hue, 63 );

  settings.redBalance = settingsRange( balance.getAxis(0) );
  settings.greenBalance = settingsRange( balance.getAxis(1) );
  settings.blueBalance = settingsRange( balance.getAxis(2) );
}


bool ofxLoopin::grabber::PS3Eye::renderSetup() {
  PS3EyeSettings next;
  controlsToSettings( next );

  bool refresh = false;

  if ( 
    next.deviceID != _settings.deviceID 
    || next.half != _settings.half 
    || next.format != _settings.format 
  
  ) {
    refresh = true;
    cerr << "init ps3eye " <<  next.deviceID << endl;


    if ( next.deviceID )
      grabber.setGrabber(std::make_shared<ofxPS3EyeGrabber>( next.deviceID ));
    else 
      grabber.setGrabber(std::make_shared<ofxPS3EyeGrabber>());

    grabber.setDesiredFrameRate( next.rate );
    grabber.setPixelFormat( OF_PIXELS_RGB );

    if ( next.half )
      grabber.setup( 320, 240, true );
    else 
      grabber.setup( 640, 480, true );

    _settings.deviceID = next.deviceID;
    _settings.half = next.half;
    _settings.rate = next.rate;
    _settings.format = next.format;
    
    refresh = true;
  }

  shared_ptr<ofxPS3EyeGrabber> eye = grabber.getGrabber<ofxPS3EyeGrabber>();

  if ( !eye ) 
    return false;

  if ( refresh || next.autoGain != _settings.autoGain ) 
    eye->setAutogain( next.autoGain );

  if ( refresh || next.autoWhiteBalance != _settings.autoWhiteBalance ) 
    eye->setAutoWhiteBalance( next.autoWhiteBalance );

  if ( refresh || next.flipHorizontal != _settings.flipHorizontal ) 
    eye->setFlipHorizontal( next.flipHorizontal );

  if ( refresh || next.flipVertical != _settings.flipVertical ) 
    eye->setFlipVertical( next.flipVertical );

  if ( refresh || next.gain != _settings.gain ) 
    eye->setGain( next.gain );

  if ( refresh || next.exposure != _settings.exposure ) 
    eye->setExposure( next.exposure );

  if ( refresh || next.sharpness != _settings.sharpness ) 
    eye->setSharpness( next.sharpness );

  if ( refresh || next.contrast != _settings.contrast ) 
    eye->setContrast( next.contrast );

  if ( refresh || next.brightness != _settings.brightness ) 
    eye->setBrightness( next.brightness );

  if ( refresh || next.hue != _settings.hue ) 
    eye->setHue( next.hue );

  if ( refresh || next.redBalance != _settings.redBalance ) 
    eye->setRedBalance( next.redBalance );

  if ( refresh || next.greenBalance != _settings.greenBalance ) 
    eye->setGreenBalance( next.greenBalance );

  if ( refresh || next.blueBalance != _settings.blueBalance ) 
    eye->setBlueBalance( next.blueBalance );

  _settings = next;

  return true;
}
