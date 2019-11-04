#pragma once

#include "./control/Control.hpp"


class ofxLoopinHasInfo {
public:
  virtual ofJson infoGet() {
    return ofJson();
  };
};
