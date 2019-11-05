#pragma once

#include "./control/Control.hpp"
#include "./Root.hpp"

namespace ofxLoopin { namespace base {
class Loader : public ofxLoopin::control::Control {
public:
  virtual void load() {};
  string getFilePath();

protected:
  void patchLocal( const ofJson & value );

  string filePath;
};
}};