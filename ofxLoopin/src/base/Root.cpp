#include "./Root.hpp"

void ofxLoopin::base::Root::addRootControls () {
  root = this;
  addSubControl("buffer", &buffers );
}
