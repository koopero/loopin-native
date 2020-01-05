#pragma once
#include "../render/Render.hpp"
#include "../control/Enable.hpp"

#include "ofxOpenCv.h"

namespace ofxLoopin { namespace blobs {

class Blobs : public ofxLoopin::render::Render {
public: 
  ofxLoopin::control::Enable enable;
  ofxLoopin::control::Enable show;
  ofxLoopin::control::Enable dispatchBlobs;
  ofxLoopin::control::Reference<ofxLoopin::base::Buffer,ofxLoopin::base::HasBuffers> pixels;

  ofxLoopin::control::Int minArea = 16;
  ofxLoopin::control::Int maxArea = 256;
  ofxLoopin::control::Int count = 16;
  ofxLoopin::control::Bool holes = false;
  ofxLoopin::control::Bool approx = true;
  
  void renderBuffer( ofxLoopin::base::Buffer * buffer );

protected:
  void addSubControls() {
    addSubControl("enable", &enable );
    addSubControl("show", &show );
    addSubControl("dispatch", &dispatchBlobs );
    addSubControl("pixels", &pixels );

    addSubControl("minArea", &minArea );
    addSubControl("maxArea", &maxArea );
    addSubControl("count", &count );
    addSubControl("holes", &holes );
    addSubControl("approx", &approx );
  };

private:
  ofxCvGrayscaleImage cvImage;
  ofxCvContourFinder contourFinder;

  float _normWidth;
  float _normHeight;
  float _normMinArea;
  float _normMaxArea;

  ofFloatColor normalizeBlob0( const ofxCvBlob & blob );
  ofFloatColor normalizeBlob1( const ofxCvBlob & blob );
  void renderBlobData( ofxLoopin::base::Buffer * buffer );
  void _dispatchBlobs();

  bool _hasRenderedBlobs = false;
};

}}; //namespace ofxLoopin:blobs