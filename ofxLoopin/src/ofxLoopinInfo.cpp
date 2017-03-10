#include "ofxLoopinInfo.h"

#include "ofxLoopinWaveform.h"

void ofxLoopinInfo::readLocal( Json::Value & value ) {
  value = readSystemInfo();
}

Json::Value ofxLoopinInfo::readSystemInfo() {
  Json::Value result;
  result["waveform"] = ofxLoopinWaveform::getInfo();
  return result;
}
