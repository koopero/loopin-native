#pragma once
#include "../render/Render.hpp"

#include "ofxOpenCv.h"

namespace ofxLoopin { namespace blobs {

class Blobs : public ofxLoopin::render::Render {
public: 
  ofxLoopin::control::Int minArea;
  ofxLoopin::control::Int maxArea;
  ofxLoopin::control::Int count;
  ofxLoopin::control::Bool holes;
  ofxLoopin::control::Bool approx;
  
  void renderBuffer( ofxLoopin::base::Buffer * buffer );

protected:
  void addSubControls() {
    addSubControl("minArea", &minArea );
    addSubControl("maxArea", &maxArea );
    addSubControl("count", &count );
    addSubControl("holes", &holes );
    addSubControl("approx", &approx );

    // cvImage.allocate( 320, 240 );
    // cvGrayImage.allocate( 320, 240 );
  };

private:
  ofxCvGrayscaleImage cvImage;

  ofxCvContourFinder contourFinder;

};

}}; //namespace ofxLoopin:blobs