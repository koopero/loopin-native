#include "./Grabber.hpp"

ofJson ofxLoopin::grabber::GrabberList::infoGet() {
  ofJson result;

  result["devices"] = ofJson::array();

  ofVideoGrabber grabber;
  std::vector<ofVideoDevice> devices = grabber.listDevices();
  int ji = 0;
  for ( int i = 0; i < devices.size(); i ++ ) {
    result["devices"][ji]["deviceID"] = i;
    result["devices"][ji]["deviceName"] = devices[i].deviceName;
    result["devices"][ji]["hardwareName"] = devices[i].hardwareName;
    result["devices"][ji]["serialID"] = devices[i].serialID;
    result["devices"][ji]["available"] = devices[i].bAvailable;
    ji++;
  }

  return result;
}
