#pragma once

#include "ofMain.h"

#include "ofxLoopinControlBool.h"
#include "ofxLoopinRender.h"
#include "ofxLoopinShader.h"


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
  void readLocal( ofJson & value );

  void addSubControls();

private:
  ofxKinect * kinect;
  ofxLoopinBuffer * renderDepth();

  bool status;

  ofxKinect::LedMode _modeLed = ofxKinect::LedMode::LED_DEFAULT;
  bool _modeInfrared = false;
  int _modeTilt = 0;
  float _triedOpening = -100; // From ofGetElapsedTimef()

  void renderBufferParams( ofxLoopinBuffer * buffer );

  void drawVideo( const ofRectangle & crop, const ofRectangle & area );
  void drawDepth( const ofRectangle & crop, const ofRectangle & area );
  void drawBoth( const ofRectangle & area );


  static ofxLoopinShader _bothShader;

};
