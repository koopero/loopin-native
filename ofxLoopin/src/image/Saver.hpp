#pragma once

#include "ofImage.h"
#include "ofThread.h"

#include "./control/Enum.hpp"
#include "../render/Render.hpp"
#include "./clock/Frame.hpp"
#include "./control/Map.hpp"

namespace ofxLoopin { namespace image {
class SaverThread : public ofThread {
public:
  void save(
    const string & dest,
    ofPixels data,
    ofxLoopin::control::Event event,
    ofImageFormat format = OF_IMAGE_FORMAT_PNG,
    ofImageQualityType qualityLevel = OF_IMAGE_QUALITY_BEST
  );

  std::vector<ofxLoopin::control::Event> flushEvents();

private:
  string dest_;
  ofPixels data_;
  ofImageFormat format_;
  ofImageQualityType qualityLevel_;
  ofxLoopin::control::Event event_;

  std::vector<ofxLoopin::control::Event> events_;

  void threadedFunction();

};

class Saver : public ofxLoopin::render::Render {
public:

  string pattern;
  string dest;
  int iterations = 0;

  ofxLoopin::control::Enum<ofImageFormat, OF_IMAGE_FORMAT_PNG> format;
  ofxLoopin::control::Enum<ofImageQualityType, OF_IMAGE_QUALITY_BEST> quality;

  void renderBuffer( ofxLoopin::base::Buffer * buffer );

protected:
  void updateLocal();

  void patchLocal( const ofJson & value );
  void patchString( string value );

  void addSubControls() {
    addSubControl("dest", new ofxLoopin::control::Value( &dest ) );
    // addSubControl("iterations", new ofxLoopin::control::Value( &iterations ) );

    format.enumAddOption("png",  OF_IMAGE_FORMAT_PNG );
    format.enumAddOption("jpeg", OF_IMAGE_FORMAT_JPEG );
    format.enumAddOption("jpg",  OF_IMAGE_FORMAT_JPEG );
    addSubControl("format", &format);

    quality.enumAddOption("best",OF_IMAGE_QUALITY_BEST);
    quality.enumAddOption("high",OF_IMAGE_QUALITY_HIGH);
    quality.enumAddOption("medium",OF_IMAGE_QUALITY_MEDIUM);
    quality.enumAddOption("low",OF_IMAGE_QUALITY_LOW);
    quality.enumAddOption("worst",OF_IMAGE_QUALITY_WORST);
    addSubControl("quality", &quality);
  };

  ofxLoopin::clock::Frame lastFrame;

  SaverThread * thread;
};
}};