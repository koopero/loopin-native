#pragma once

#include "ofMain.h"

#include "../control/Bool.hpp"
#include "../render/Render.hpp"
#include "../shader/Shader.hpp"
#include "../control/Enable.hpp"


#include "ofxKinect.h"

/** loopin/type/ofxLoopinKinect
subs/tilt:
  type: number
  min: -30
  max: 30

subs/output:
  type: options
  options:
    - both
    - depth
    - video
    - alpha

subs/led:
  type: options
  options:
    - default
    - off
    - green
    - red
    - yellow
    - blinkGreen
    - blinkYellowRed

subs/infrared:
  type: bool

**/

namespace ofxLoopin { namespace kinect {
class Kinect : public ofxLoopin::render::Render {
public:
  ofxLoopin::control::Enable enable;

  int deviceId = -1;
  int fill = 0;

  enum Output {
    OUTPUT_VIDEO,
    OUTPUT_DEPTH,
    OUTPUT_BOTH,
    OUTPUT_ALPHA
  };

  ofxLoopin::control::Enum<ofxKinect::LedMode, ofxKinect::LedMode::LED_DEFAULT> led;
  ofxLoopin::control::Enum<Output, OUTPUT_BOTH> output;
  ofxLoopin::control::Bool infrared;
  ofxLoopin::control::Bool registration;

  ofxLoopin::control::Number tilt;

  void updateTilt() {
    float tilt = ofxLoopin::kinect::Kinect::tilt;

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

  void renderBuffer( ofxLoopin::base::Buffer * buffer );


protected:
  void updateLocal();
  void readLocal( ofJson & value );

  void addSubControls();

private:
  ofxKinect * kinect;
  ofxLoopin::base::Buffer * renderDepth();

  bool status;

  ofxKinect::LedMode _modeLed = ofxKinect::LedMode::LED_DEFAULT;
  bool _modeInfrared = false;
  bool _modeRegistration = false;

  int _modeTilt = 0;
  float _triedOpening = -100; // From ofGetElapsedTimef()

  void renderBufferParams( ofxLoopin::base::Buffer * buffer );

  void drawVideo( const ofRectangle & crop, const ofRectangle & area );
  void drawDepth( const ofRectangle & crop, const ofRectangle & area );
  void drawBoth( const ofRectangle & area );

  void closeKinect();

  static ofxLoopin::shader::Shader _bothShader;

};
}};