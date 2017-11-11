#pragma once

#include "ofxLoopinControl.h"


class ofxLoopinHasInfo {
public:
  virtual Json::Value infoGet() {
    return Json::nullValue;
  };
};
