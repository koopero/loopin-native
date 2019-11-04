/** loopin/type/input:
*/

#pragma once

#include "ofMain.h"

class ofxLoopinInput : public ofxLoopin::control::Control {
public:
  // openFrameworks mouse events
  void mouseMoved(ofMouseEventArgs & args) {
    dispatchMouseEvent("mousemove", args );
  };
  void mouseDragged(ofMouseEventArgs & args) {
    dispatchMouseEvent("mousemove", args );
  };
  void mousePressed(ofMouseEventArgs & args) {
    dispatchMouseEvent("mousedown", args );
  };
  void mouseReleased(ofMouseEventArgs & args) {
    dispatchMouseEvent("mouseup", args );
  };
  void mouseScrolled(ofMouseEventArgs & args) {};
  void mouseEntered(ofMouseEventArgs & args) {
    dispatchMouseEvent("mouseenter", args );
  };
  void mouseExited(ofMouseEventArgs & args) {
    dispatchMouseEvent("mouseexit", args );
  };

protected:

  void addSubControls() {
    ofRegisterMouseEvents(this);
  }

  void dispatchMouseEvent( const string & type, ofMouseEventArgs &args ) {
    ofxLoopin::control::Event event;
    event.type = type;
    event.data["x"] = (float) ofGetMouseX() / ofGetWindowWidth() * 2.0 - 1.0;
    event.data["y"] = (float) ofGetMouseY() / ofGetWindowHeight() * 2.0 - 1.0;

    if ( args.button )
      event.data["button"] = args.button;

    dispatch( event );
  }
};
