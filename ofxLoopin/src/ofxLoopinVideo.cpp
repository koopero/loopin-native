#include "ofxLoopinVideo.h"

// void ofxLoopinVideo::readLocal( ofJson & value ) {
//   std::cerr << "ofxLoopinVideo::readLocal" << endl;
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

void ofxLoopinVideo::patchLocal( const ofJson & value ) {
  // std::cerr << "ofxLoopinVideo::patchLocal " << value << endl;

  if ( value.is_object() && value.count("src") && value["src"].is_string() ) {
    string videoPath = value["src"].get<std::string>();
    string absPath = ofxLoopinFile::find( videoPath );

    if ( absPath.size() ) {
      player.load( absPath );
    } else {
      ofxLoopinEvent event;
      event.type = "error";
      dispatch( event );
    }
  }
};

void ofxLoopinVideo::patchString( string value ) {
  ofJson patch;
  patch["src"] = value;
  patchLocal( patch );
};


double ofxLoopinVideo::getPlayerTime() {
  return getPlayerTime( player.getCurrentFrame() );
}

double ofxLoopinVideo::getPlayerTime( int frame ) {
  float duration = player.getDuration();
  // int numFrames = player.getTotalNumFrames();
  // double rate = numFrames / duration;

  float position = player.getPosition();
  double time = position * duration;

  return time;
}

void ofxLoopinVideo::renderBuffer( ofxLoopinBuffer * buffer ) {

  if ( player.isPaused() ) {
    // std::cerr << "no delta "<< endl;
    renderingFrame.delta = 0;
  }

  clock.advance( renderingFrame );



  int numFrames = player.getTotalNumFrames();

  if ( !numFrames )
    return;


  float duration = player.getDuration();


  double rate = numFrames / duration;

  clock.rate = rate;

  double syncTo = clock.frame.time;

  syncTo = fmod( syncTo, duration );
  if ( syncTo < 0 )
    syncTo += duration;


  int syncFrame = syncTo / duration * numFrames;


  ofxLoopinEvent event;
  event.type = "videoFrame";


  int frame = player.getCurrentFrame();


  int syncTolerance = 10;
  bool shouldDispatch = false;

  switch( clock.mode.getEnumValue() ) {
    case ofxLoopinFrame::Mode::STEP:
      player.setSpeed(0);
      // player.update();

      if ( clock.frame.speed ) {
        syncFrame = frame + 1;
        syncFrame = syncFrame % numFrames;
        syncTo = syncFrame / rate;
        syncTolerance = 0;
        shouldDispatch = true;
      }


    break;

    case ofxLoopinFrame::Mode::TIME:
    case ofxLoopinFrame::Mode::FRAME:
      player.setSpeed( clock.frame.speed );
      player.play();
      // player.update();
    break;
  }



  float position = player.getPosition();
  double time = position * duration;

  event.data["rate"] = rate;

  event.data["running"] = (bool) clock.running;

  event.data["frame"] = frame;
  event.data["frameSpeed"] = clock.frame.speed;

  event.data["time"] = time;
  // event.data["sync"] = sync;
  event.data["syncTo"] = syncTo;


  event.data["position"] = position;
  event.data["clock"]["time"] = clock.frame.time;


  int sync = syncFrame - frame;
  if ( abs( sync ) > syncTolerance ) {
    event.data["syncFrame"] = syncFrame;

    if ( sync == 1 ) {
      player.nextFrame();
    } else {
      player.setFrame( syncFrame );
    }


    time = syncFrame / rate;
  }

  player.update();
  clock.frame.time = getPlayerTime();


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
