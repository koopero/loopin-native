#pragma once

#include "../control/Control.hpp"
#include "./Root.hpp"

namespace ofxLoopin { namespace base {
class Reader : public ofxLoopin::control::Control {
protected:
  void patchString( string value );
};
}};