#pragma once

#include "ofSoundStream.h"

#include "ofxLoopinControlBool.h"
#include "ofxLoopinControlEnum.h"
#include "ofxLoopinControlNumber.h"

#include "ofxLoopinRender.h"

/** loopin/type/shader
sub:
  buffer:
    map: buffer
    sub/type: buffer

  phase:
    options:
      - abs
      - pos
      - neg
      - both

  duration:
    type: float
    unit: s
    time: true
    min: 0.001
    max: 30

  squelch:
    type: float
    min: 0
    max: 1

  gain:
    type: float
    min: 0
    max: 30

*/
class ofxLoopinWaveform : public ofxLoopinRender, public ofBaseSoundInput {
public:
  enum Phase {
    PHASE_ABS,
    PHASE_POS,
    PHASE_NEG,
    PHASE_BOTH
  };

  ofxLoopinControlEnum<ofxLoopinWaveform::Phase, PHASE_ABS> phase;
  ofxLoopinControlNumber duration = 1;
  ofxLoopinControlNumber squelch = 0;
  ofxLoopinControlNumber gain = 1;
  ofxLoopinControlInt channels = 2;
  ofxLoopinControlInt deviceID = 0;




  void renderBuffer( ofxLoopinBuffer * buffer );
  void audioIn(ofSoundBuffer &buffer);

  ofRectangle getBounds();

  static Json::Value getInfo();

protected:
  bool streamIsOpen = false;
  int _deviceID = -1;
  ofSoundStream soundStream;
  ofSoundBuffer samples;

  void computeSample( float & sample, float & sign );
  // void patchLocal( const Json::Value & value );
  // void patchString( const string & value );

  void addSubControls() {
    addSubControl("buffer", &buffer );

    phase.setEnumKey("abs", PHASE_ABS );
    phase.setEnumKey("pos", PHASE_POS );
    phase.setEnumKey("neg", PHASE_NEG );
    phase.setEnumKey("both", PHASE_BOTH );
    addSubControl("phase", &phase );

    addSubControl("squelch", &squelch );
    addSubControl("gain", &gain);
    addSubControl("duration", &duration );
    addSubControl("channels", &channels );
  };
};
