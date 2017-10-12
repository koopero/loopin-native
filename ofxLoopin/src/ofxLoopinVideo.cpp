#include "ofxLoopinVideo.h"

// void ofxLoopinVideo::readLocal( Json::Value & value ) {
//   cerr << "ofxLoopinVideo::readLocal" << endl;
//   if ( _video.isLoaded() ) {
//     value["loaded"] = true;
//     value["width"] = _video.getWidth();
//     value["height"] = _video.getHeight();
//     value["src"] = _video.getMoviePath();
//     value["duration"] = _video.getDuration();
//     value["play"] = _video.isPlaying();
//     value["videoFrame"] = _video.getCurrentFrame();
//   } else {
//     value["loaded"] = false;
//   }
// };


void ofxLoopinVideo::renderBuffer( ofxLoopinBuffer * buffer ) {

  clock.advance( renderingFrame );



  int numFrames = player.getTotalNumFrames();

  float duration = player.getDuration();


  double rate = numFrames / duration;

  double syncTo = clock.frame.time;

  syncTo = fmod( syncTo, duration );
  if ( syncTo < 0 )
    syncTo += duration;


  int syncFrame = syncTo / duration * numFrames;


  ofxLoopinEvent event;
  event.type = "videoFrame";


  int frame = player.getCurrentFrame();


  int syncTolerance = 3;

  bool shouldDispatch = false;

  switch( clock.mode.getEnumValue() ) {
    case ofxLoopinClock::STEP:
      player.setSpeed(0);

      if ( clock.frame.speed ) {
        syncFrame = frame + 1;
        syncFrame = syncFrame % numFrames;
        syncTo = syncFrame / rate;
        syncTolerance = 0;
        shouldDispatch = true;
      }


    break;

    case ofxLoopinClock::TIME:
    case ofxLoopinClock::FRAME:
      player.setSpeed( clock.frame.speed );
      player.play();
      player.update();
    break;
  }

  int sync = syncFrame - frame;


  float position = player.getPosition();
  double time = position * duration;

  event.data["rate"] = rate;

  event.data["running"] = (bool) clock.running;

  event.data["frame"] = frame;
  event.data["frameSpeed"] = clock.frame.speed;

  event.data["time"] = time;
  event.data["sync"] = sync;
  event.data["syncTo"] = syncTo;


  event.data["position"] = position;
  event.data["clock"] = clock.frame.time;


  if ( abs( sync ) > syncTolerance ) {
    event.data["syncFrame"] = syncFrame;

    if ( sync == 1 ) {
      player.nextFrame();
      player.update();
    } else {
      player.setFrame( syncFrame );
      player.update();
    }

    time = syncFrame / rate;
    clock.frame.time = time;

    shouldDispatch = true;
  }

  if ( shouldDispatch )
    dispatch( event );



  if ( !player.isFrameNew() )
    return;

  ofRectangle bounds = ofRectangle( 0,0, player.getWidth(), player.getHeight() );

  if ( buffer == nullptr )
    buffer = getBuffer( true );

  buffer->defaultSize( bounds );

  if ( !buffer->begin() ) {
    // TODO: Error here
    return;
  }


  player.draw( 0, 0, buffer->getWidth(), buffer->getHeight() );

  buffer->end();
};
