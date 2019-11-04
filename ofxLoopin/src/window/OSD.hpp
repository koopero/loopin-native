#pragma once

#include "./control/Control.hpp"
#include "./control/Value.hpp"
#include "../ofxLoopinFile.h"
#include "../ofxLoopinFrame.h"

#include "ofMain.h"

#include <unistd.h>

/** loopin/type/osd:
  sub/enabled/type: bool
  sub/text/type: string
  sub/client/type: string
*/

namespace ofxLoopin { namespace window {

class OSD : public ofxLoopin::control::Control {
public:
  bool enabled = true;

  string defaultString = {
    "   fps: %fps\n"
    "  show: %show\n"
    "window: %window\n"
    "  host: %hostname"
  };

  string text;
  string show;
  string hostname;
  string client;

  void setFrame( const ofxLoopinFrame & frame );
  void draw();

protected:

  ofxLoopinFrame _frame;

  void addSubControls() override;

private:
  void templatize( string & str, const string & key, float value );
  void templatize( string & str, const string & key, const string & replacement );
};
}};
