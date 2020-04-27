#pragma once

#include "../control/Control.hpp"
#include "../control/Colour.hpp"
#include "../control/Enable.hpp"
#include "../control/Value.hpp"
#include "../control/Vector.hpp"
#include "../base/File.hpp"
#include "../clock/Frame.hpp"

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
  control::Enable enable;
  control::Colour colour;
  control::Colour background;
  control::Vector<2> position;

  string defaultString = {
    "   fps: %fps\n"
    "  show: %show\n"
    "window: %window\n"
    "  host: %hostname"
  };

  string window;
  string text;
  string show;
  string hostname;
  string client;

  void setFrame( const ofxLoopin::clock::Frame & frame );
  void draw();

protected:

  ofxLoopin::clock::Frame _frame;

  void addSubControls() override;
  void patchLocal( const ofJson & val ) override;

private:
  void templatize( string & str, const string & key, float value );
  void templatize( string & str, const string & key, const string & replacement );
};
}};
