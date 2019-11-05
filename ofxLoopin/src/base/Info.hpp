#pragma once

#include "../control/Control.hpp"
#include "./HasInfo.hpp"
#include "./Root.hpp"


namespace ofxLoopin { namespace base {
class Info : public ofxLoopin::control::Control {
protected:
  void readLocal( ofJson & value );
  ofJson getInfo();
  ofJson getInfoKey( const string & key );
};
}};
