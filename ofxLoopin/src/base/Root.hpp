#pragma once

#include "./Buffer.hpp"
#include "./control/Control.hpp"
#include "./clock/Frame.hpp"

namespace ofxLoopin { namespace base {
class Root : public ofxLoopin::control::Control, public ofxLoopin::base::HasBuffers {
public:
  // string resolveFilePath( string path );
  ofxLoopin::clock::Frame frame;


protected:
  void addRootControls();
};
}};