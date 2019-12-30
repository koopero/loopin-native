#include "./Frame.hpp"

ofxLoopin::control::Event ofxLoopin::clock::Frame::asEvent () {
  ofxLoopin::control::Event event = ofxLoopin::control::Event("frame");
  event.data["index"] = index;
  event.data["time"] = time;
  event.data["delta"] = delta;
  event.data["speed"] = speed;
  event.data["rate"] = rate;

  return event;
}
