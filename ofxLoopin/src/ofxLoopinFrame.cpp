#include "ofxLoopinFrame.h"



ofxLoopin::control::Event ofxLoopinFrame::asEvent () {
  ofxLoopin::control::Event event = ofxLoopin::control::Event("frame");
  event.data["index"] = index;
  event.data["time"] = time;
  event.data["delta"] = delta;
  event.data["speed"] = speed;

  return event;
}
