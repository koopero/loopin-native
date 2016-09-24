#include "ofxLoopinRoot.h"

void ofxLoopinRoot::addRootControls () {
  root = this;
  addSubControl("buffer", &buffers );
}
