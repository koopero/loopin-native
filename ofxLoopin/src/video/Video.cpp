#include "./Video.hpp"

// void ofxLoopin::video::Video::readLocal( ofJson & value ) {
//   std::cerr << "ofxLoopin::video::Video::readLocal" << endl;
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

void ofxLoopin::video::Video::patchLocal( const ofJson & value ) {
  // std::cerr << "ofxLoopin::video::Video::patchLocal " << value << endl;

  if ( value.is_object() && value.count("file") && value["file"].is_string() ) {
    loadFile ( value["file"].get<std::string>() );
  }

  // std::cerr << "ofxLoopin::video::Video::patchLocal after " << endl;
};

void ofxLoopin::video::Video::loadFile( const string & file ) {
  string videoPath = file;
  string absPath = ofxLoopinFile::find( videoPath );

  wasLoaded = false;
  if ( absPath.size() ) {
    engine->load( absPath );
  } else {
    ofxLoopinEvent event;
    event.type = "error";
    dispatch( event );
  }
};


void ofxLoopin::video::Video::patchString( string value ) {
  ofJson patch;
  patch["file"] = value;
  patchLocal( patch );
};

void ofxLoopin::video::Video::onLoaded() {
  engine->loadClock( clock );
  ofxLoopinEvent event;
  event.type = "loaded";
  dispatch( event );
  wasLoaded = true;
}

void ofxLoopin::video::Video::renderBuffer( ofxLoopinBuffer * buffer ) {
  if ( !engine->isLoaded() || engine->isPaused() ) {
    // std::cerr << "no delta "<< endl;
    renderingFrame.delta = 0;
  }

  clock.advance( renderingFrame );


  float speed = clock.speed;
  // engine->setSpeed( speed );

  if ( clock.shouldSync() ) {
    engine->setFrame( clock.syncFrame() );
    sendSyncEvent = true;
  }

  switch( clock.mode.getEnumValue() ) {
    case ofxLoopinFrame::Mode::STEP:
      engine->setSpeed(0);
      if ( clock.frame.delta && !sendSyncEvent ) {
        // cerr << "next Frame " << endl;
        engine->nextFrame();
      }
    break;

    case ofxLoopinFrame::Mode::TIME:
      engine->setSpeed( clock.frame.speed );
    break;

    case ofxLoopinFrame::Mode::FRAME:
      engine->setSpeed(0);
      engine->nextFrame();
    break;

    default:
    case ofxLoopinFrame::Mode::STOP:
      engine->setSpeed(0);
    break;
  }

  engine->update();
  engine->updateClock( clock );

  if ( engine->isFrameNew() ) {
    // cerr << "Frame is new" << endl;
  } else {
    return;
  }

  // if ( engine->isPlaying() ) {

  // } else {
  //   cerr << "Not playing" << endl;
  //   return;
  // }

  ofRectangle bounds = engine->getBounds();
  buffer->defaultSize( bounds );

  if ( !buffer->begin() ) {
    return;
  }

  engine->draw( 0, 0, buffer->getWidth(), buffer->getHeight() );
  buffer->end();  

  // engine->drawToBuffer( buffer ); 

  if ( !wasLoaded && engine->isLoaded() ) {
    onLoaded();
  }

  if ( sendSyncEvent ) {
    ofxLoopinEvent event;
    event.type = "sync";
    dispatch( event );    
    sendSyncEvent = false;
  }

  if ( engine->getIsMovieDone() ) {
    ofxLoopinEvent event;
    event.type = "ended";
    dispatch( event );    
  }


  // if ( !engine->isLoaded() ) 
  //   return;

  // // videoSync();
  // // engine->play();

  // auto before = ofGetElapsedTimeMicros();
  // engine->update();
  // auto after = ofGetElapsedTimeMicros();

  // clock.frame.time = engine->getTime();



};


// bool ofxLoopin::video::Video::videoSync() {
//   int numFrames = engine->getTotalNumFrames();

//   if ( !numFrames )
//     return true;


//   float duration = engine->getDuration();
//   double rate = numFrames / duration;
//   clock.rate = rate;

//   double syncTo = clock.frame.time;
//   syncTo = fmod( syncTo, duration );
//   if ( syncTo < 0 )
//     syncTo += duration;

//   int syncFrame = syncTo / duration * numFrames;


//   ofxLoopinEvent event;
//   event.type = "videoFrame";

//   int frame = engine->getCurrentFrame();


//   int syncTolerance = 10;
//   bool shouldDispatch = false;

//   switch( clock.mode.getEnumValue() ) {
//     case ofxLoopinFrame::Mode::STEP:
//       engine->setSpeed(0);
//       // engine->update();

//       if ( clock.frame.speed ) {
//         syncFrame = frame + 1;
//         syncFrame = syncFrame % numFrames;
//         syncTo = syncFrame / rate;
//         syncTolerance = 0;
//         shouldDispatch = true;
//       }

//     break;

//     case ofxLoopinFrame::Mode::TIME:
//     case ofxLoopinFrame::Mode::FRAME:

//       // engine->setSpeed( clock.frame.speed );

//       if ( !engine->isPlaying() ) {
//         // cerr << "ofxLoopin::video::Video::videoSync playing " << clock.frame.speed << endl;
//         engine->play();
//       }
//       // engine->update();
//     break;

//     default:

//     break;
//   }
//   float position = engine->getPosition();
//   double time = position * duration;

//   event.data["rate"] = rate;
//   event.data["running"] = (bool) clock.running;
//   event.data["frame"] = frame;
//   event.data["frameSpeed"] = clock.frame.speed;
//   event.data["time"] = time;
//   // event.data["sync"] = sync;
//   event.data["syncTo"] = syncTo;


//   event.data["position"] = position;
//   event.data["clock"]["time"] = clock.frame.time;


//   int sync = syncFrame - frame;
//   if ( abs( sync ) > syncTolerance ) {
//     event.data["syncFrame"] = syncFrame;

//     if ( sync == 1 ) {
//       engine->nextFrame();
//     } else {
//       engine->setFrame( syncFrame );
//     }


//     time = syncFrame / rate;
//   }

//   return true;
// }

