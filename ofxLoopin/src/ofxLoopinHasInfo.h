#pragma once

#include "ofxLoopinControl.h"


class ofxLoopinHasInfo {
public:
  virtual ofJson infoGet() {
    return ofJson();
  };
};
