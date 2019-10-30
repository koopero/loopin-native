#include "ofxLoopinFrame.h"



ofxLoopinEvent ofxLoopinFrame::asEvent () {
  ofxLoopinEvent event = ofxLoopinEvent("frame");
  event.data["index"] = index;
  event.data["time"] = time;
  event.data["delta"] = delta;
  event.data["speed"] = speed;
  event.data["rate"] = rate;


  return event;
}
