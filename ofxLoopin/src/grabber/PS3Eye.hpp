#pragma once

#include "../base/HasInfo.hpp"
#include "../control/Number.hpp"
#include "../control/Bool.hpp"
#include "../render/Blit.hpp"

#include "ofxPS3EyeGrabber.h"

namespace ofxLoopin { namespace grabber {

class PS3EyeSettings {
public:
  int deviceID = -1;
  int rate = 60;
  ofPixelFormat format = OF_PIXELS_RGB;
  bool half = false;
  bool autoGain = false;
  bool autoWhiteBalance = false;
  uint8_t gain = 1;
  uint8_t exposure = 0;
  uint8_t sharpness = 0;
  uint8_t contrast = 0;
  uint8_t brightness = 0;
  uint8_t hue = 0;
  uint8_t redBalance = 0;
  uint8_t greenBalance = 0;
  uint8_t blueBalance = 0;
  ofxPS3EyeGrabber::DemosaicType demosaicType = ofxPS3EyeGrabber::DemosaicType::DEMOSAIC_BILINEAR;
  bool flipVertical = false;
  bool flipHorizontal = false;
  bool led = false;
  
};

class PS3Eye : public render::Blit {
public:
  control::Int deviceID = 0;
  control::Int rate = 60;
  control::Bool autoGain = true;
  control::Bool autoWhiteBalance;
  control::Bool flipVertical;
  control::Bool flipHorizontal;
  control::Bool half = false;
  control::Number gain = 1.0;
  control::Number exposure = 1.0;
  control::Number sharpness = 0.5;
  control::Number contrast = 0.5;
  control::Number brightness = 1.0;
  control::Number hue = 0;
  control::Colour balance;
  // control::Enum demosaic;

  bool renderSetup() override;

  void renderBuffer( ofxLoopin::base::Buffer * buffer ) override;

  ofRectangle getBounds() override;
  // ofTexture * textureToRender() override;

  // void renderBuffer( ofxLoopin::base::Buffer * buffer ) override;
  // ofRectangle getBounds() override;

protected:
  void addSubControls() override {
    ofxLoopin::render::Blit::addSubControls();
    addSubControl( "deviceID", &deviceID );
    addSubControl( "rate", &rate );
    addSubControl( "autoGain", &autoGain );
    addSubControl( "autoWhiteBalance", &autoWhiteBalance );
    addSubControl( "flipVertical", &flipVertical );
    addSubControl( "flipHorizontal", &flipHorizontal );
    addSubControl( "half", &half );
    addSubControl( "gain", &gain );
    addSubControl( "exposure", &exposure );
    addSubControl( "sharpness", &sharpness );
    addSubControl( "contrast", &contrast );
    addSubControl( "brightness", &brightness );
    addSubControl( "hue", &hue );
    addSubControl( "balance", &balance );
  }

  void controlsToSettings( PS3EyeSettings & settings );
  void refreshSetup();

  PS3EyeSettings _settings;
  bool _init = false;

  ofVideoGrabber grabber;
  uint8_t settingsRange( float val, uint8_t max = 255 );
};

class PS3EyeList : public ofxLoopin::render::Renders<PS3Eye>, public ofxLoopin::base::HasInfo {
public:
  ofJson infoGet();  
};

// namespace ofxLoopin::grabber
}};