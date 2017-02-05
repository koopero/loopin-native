#pragma once

#include "ofImage.h"
#include "ofThread.h"

#include "ofxLoopinControlEnum.h"
#include "ofxLoopinRender.h"
#include "ofxLoopinFrame.h"
#include "ofxLoopinMap.h"


class ofxLoopinSaverThread : public ofThread {
public:
  void save(
    const string & dest,
    ofPixels data,
    ofxLoopinEvent event,
    ofImageFormat format = OF_IMAGE_FORMAT_PNG,
    ofImageQualityType qualityLevel = OF_IMAGE_QUALITY_BEST
  );

  vector<ofxLoopinEvent> flushEvents();

private:
  string dest_;
  ofPixels data_;
  ofImageFormat format_;
  ofImageQualityType qualityLevel_;
  ofxLoopinEvent event_;

  vector<ofxLoopinEvent> events_;

  void threadedFunction();

};

class ofxLoopinSaver : public ofxLoopinRender {
public:

  string pattern;
  string dest;
  int iterations = 0;

  ofxLoopinControlEnum<ofImageFormat, OF_IMAGE_FORMAT_PNG> format;
  ofxLoopinControlEnum<ofImageQualityType, OF_IMAGE_QUALITY_BEST> quality;

  void renderBuffer( ofxLoopinBuffer * buffer );

protected:
  void updateLocal();

  void patchLocal( const Json::Value & value );
  void patchString( const string & value );

  void addSubControls() {
    addSubControl("dest", new ofxLoopinControlValue( &dest ) );
    addSubControl("iterations", new ofxLoopinControlValue( &iterations ) );

    format.setEnumKey("png",  OF_IMAGE_FORMAT_PNG );
    format.setEnumKey("jpeg", OF_IMAGE_FORMAT_JPEG );
    format.setEnumKey("jpg",  OF_IMAGE_FORMAT_JPEG );
    addSubControl("format", &format);

    quality.setEnumKey("best",OF_IMAGE_QUALITY_BEST);
    quality.setEnumKey("high",OF_IMAGE_QUALITY_HIGH);
    quality.setEnumKey("medium",OF_IMAGE_QUALITY_MEDIUM);
    quality.setEnumKey("low",OF_IMAGE_QUALITY_LOW);
    quality.setEnumKey("worst",OF_IMAGE_QUALITY_WORST);
    addSubControl("quality", &quality);
  };

  ofxLoopinFrame lastFrame;

  ofxLoopinSaverThread * thread;

};
