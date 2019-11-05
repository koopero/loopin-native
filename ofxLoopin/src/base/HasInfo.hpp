#pragma once

#include "../control/Control.hpp"

namespace ofxLoopin { namespace base {
class HasInfo {
public:
  virtual ofJson infoGet() {
    return ofJson();
  };
};
}};
