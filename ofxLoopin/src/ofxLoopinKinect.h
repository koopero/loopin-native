#pragma once

#include "ofxLoopinControlBool.h"
#include "ofxLoopinRender.h"

#include "ofxKinect.h"

/** loopin/type/kinect
sub/tilt:
  type: number
  min: -30
  max: 30

sub/output:
  type: options
  options:
    - both
    - depth
    - video
    - alpha

sub/led:
  type: options
  options:
    - default
    - off
    - green
    - red
    - yellow
    - blinkGreen
    - blinkYellowRed

sub/infrared:
  type: bool

**/

class ofxLoopinKinect : public ofxLoopinRender {
public:
  int deviceId = -1;
  int fill = 0;

  enum Output {
    OUTPUT_VIDEO,
    OUTPUT_DEPTH,
    OUTPUT_BOTH,
    OUTPUT_ALPHA
  };

  ofxLoopinControlEnum<ofxKinect::LedMode, ofxKinect::LedMode::LED_DEFAULT> led;
  ofxLoopinControlEnum<ofxLoopinKinect::Output, OUTPUT_BOTH> output;
  ofxLoopinControlBool infrared;


  ofxLoopinControlNumber tilt;

  void updateTilt() {
    float tilt = ofxLoopinKinect::tilt;

    if ( tilt != kinect->getTargetCameraTiltAngle() ) {
      kinect->setCameraTiltAngle( tilt );
    }
  }

  void updateLed() {
    if ( _modeLed != led.getEnumValue() ) {
      kinect->setLed( led.getEnumValue() );
      _modeLed = led.getEnumValue();
    }
  }

  void renderBuffer( ofxLoopinBuffer * buffer );


protected:
  void updateLocal();
  void readLocal( Json::Value & value );

  void addSubControls() {

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

private:
  ofxKinect * kinect;
  ofxLoopinBuffer * renderDepth();

  bool status;

  ofxKinect::LedMode _modeLed = ofxKinect::LedMode::LED_DEFAULT;
  bool _modeInfrared = false;
  int _modeTilt = 0;

  void renderBufferParams( ofxLoopinBuffer * buffer );

  void drawVideo( const ofRectangle & crop, const ofRectangle & area );
  void drawDepth( const ofRectangle & crop, const ofRectangle & area );

};
