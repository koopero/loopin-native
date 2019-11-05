#pragma once

#include "ofSoundStream.h"

#include "../base/HasInfo.hpp"
#include "./control/Bool.hpp"
#include "./control/Enum.hpp"
#include "./control/Number.hpp"
#include "../render/Render.hpp"
#include "../shader/Shader.hpp"
#include "../control/Enable.hpp"


#include <mutex>



namespace ofxLoopin { namespace render {

class waveform_imp;

class waveform : public ofxLoopin::render::Renders<waveform_imp>, public ofxLoopin::base::HasInfo {
public:
  ofJson infoGet();
};

class waveform_imp : public ofxLoopin::render::Render, public ofBaseSoundInput {
public:
  ofxLoopin::control::Enable enable;

  enum Phase {
    PHASE_ABS,
    PHASE_POS,
    PHASE_NEG,
    PHASE_BOTH
  };
  
  ofxLoopin::control::Enum<waveform_imp::Phase, PHASE_ABS> phase;
  ofxLoopin::control::Number duration = 0;
  ofxLoopin::control::Number squelch = 0;
  ofxLoopin::control::Number gain = 1;
  ofxLoopin::control::Number test = 0;
  ofxLoopin::control::Int y = 0;
  ofxLoopin::control::Int channels = 2;
  ofxLoopin::control::Int deviceID = 0;

  void renderBuffer( ofxLoopin::base::Buffer * buffer );
  void audioIn(ofSoundBuffer &buffer);

  ofRectangle getBounds();

  static ofJson getInfo();

protected:
  std::mutex samples_mutex;
  bool streamIsOpen = false;
  int _deviceID = -1;
  ofSoundStream soundStream;
  ofSoundBuffer samples;

  void renderScrollExisting( ofxLoopin::base::Buffer * buffer, int offset );

  void computeSample( float & sample, int & sign );
  void drawSample( int x, int y, float sample );

  void addSubControls() {
    enable.setKey("no");

    addSubControl("enable", &enable );

    addSubControl("buffer", &buffer );
    addSubControl("deviceID", &deviceID );

    phase.enumAddOption("abs", PHASE_ABS );
    phase.enumAddOption("pos", PHASE_POS );
    phase.enumAddOption("neg", PHASE_NEG );
    phase.enumAddOption("both", PHASE_BOTH );
    addSubControl("phase", &phase );

    addSubControl("squelch", &squelch );
    addSubControl("gain", &gain);
    addSubControl("test", &test );
    addSubControl("duration", &duration );
    addSubControl("channels", &channels );
    addSubControl("y", &y );

  };

  static ofxLoopin::shader::Shader shader;
  static ofxLoopin::shader::Shader scrollShader;

  void closeStream();
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
