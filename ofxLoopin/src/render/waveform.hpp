#pragma once

#include "ofSoundStream.h"

#include "ofxLoopinHasInfo.h"
#include "ofxLoopinControlBool.h"
#include "ofxLoopinControlEnum.h"
#include "ofxLoopinControlNumber.h"
#include "ofxLoopinRender.h"
#include "ofxLoopinShader.h"


#include <mutex>



namespace ofxLoopin { namespace render {

class waveform_imp;

class waveform : public ofxLoopinRenders<waveform_imp>, public ofxLoopinHasInfo {
public:
  Json::Value infoGet();
};

class waveform_imp : public ofxLoopinRender, public ofBaseSoundInput {
public:
  enum Phase {
    PHASE_ABS,
    PHASE_POS,
    PHASE_NEG,
    PHASE_BOTH
  };

  ofxLoopinControlEnum<waveform_imp::Phase, PHASE_ABS> phase;
  ofxLoopinControlNumber duration = 0;
  ofxLoopinControlNumber squelch = 0;
  ofxLoopinControlNumber gain = 1;
  ofxLoopinControlInt y = 0;
  ofxLoopinControlInt channels = 2;
  ofxLoopinControlInt deviceID = 0;

  void renderBuffer( ofxLoopinBuffer * buffer );
  void audioIn(ofSoundBuffer &buffer);

  ofRectangle getBounds();

  static Json::Value getInfo();

protected:
  std::mutex samples_mutex;
  bool streamIsOpen = false;
  int _deviceID = -1;
  ofSoundStream soundStream;
  ofSoundBuffer samples;

  void renderScrollExisting( ofxLoopinBuffer * buffer, int offset );

  void computeSample( float & sample, int & sign );
  void drawSample( int x, int y, float sample );

  void addSubControls() {

    addSubControl("buffer", &buffer );
    addSubControl("deviceID", &deviceID );

    phase.setEnumKey("abs", PHASE_ABS );
    phase.setEnumKey("pos", PHASE_POS );
    phase.setEnumKey("neg", PHASE_NEG );
    phase.setEnumKey("both", PHASE_BOTH );
    addSubControl("phase", &phase );

    addSubControl("squelch", &squelch );
    addSubControl("gain", &gain);
    addSubControl("duration", &duration );
    addSubControl("channels", &channels );
    addSubControl("y", &y );

  };

  static ofxLoopinShader shader;
};
/** loopin/type/waveform
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
}}
