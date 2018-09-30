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

  if ( value.is_object() && value.count("src") && value["src"].is_string() ) {
    string videoPath = value["src"].get<std::string>();
    string absPath = ofxLoopinFile::find( videoPath );
    // std::cerr << "ofxLoopin::video::Video::patchLocal loading " << videoPath << " " << absPath << endl;

    wasLoaded = false;
    if ( true || absPath.size() ) {

      engine->load( videoPath );
    } else {
      ofxLoopinEvent event;
      event.type = "error";
      dispatch( event );
    }
  }

  // std::cerr << "ofxLoopin::video::Video::patchLocal after " << endl;

};

void ofxLoopin::video::Video::patchString( string value ) {
  ofJson patch;
  patch["src"] = value;
  patchLocal( patch );
};


bool ofxLoopin::video::Video::videoSync() {
  int numFrames = engine->getTotalNumFrames();

  if ( !numFrames )
    return true;


  float duration = engine->getDuration();
  double rate = numFrames / duration;
  clock.rate = rate;

  double syncTo = clock.frame.time;
  syncTo = fmod( syncTo, duration );
  if ( syncTo < 0 )
    syncTo += duration;

  int syncFrame = syncTo / duration * numFrames;


  ofxLoopinEvent event;
  event.type = "videoFrame";

  int frame = engine->getCurrentFrame();


  int syncTolerance = 10;
  bool shouldDispatch = false;

  switch( clock.mode.getEnumValue() ) {
    case ofxLoopinFrame::Mode::STEP:
      engine->setSpeed(0);
      // engine->update();

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

      // engine->setSpeed( clock.frame.speed );

      if ( !engine->isPlaying() ) {
        // cerr << "ofxLoopin::video::Video::videoSync playing " << clock.frame.speed << endl;
        engine->play();
      }
      // engine->update();
    break;

    default:

    break;
  }
  float position = engine->getPosition();
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
      engine->nextFrame();
    } else {
      engine->setFrame( syncFrame );
    }


    time = syncFrame / rate;
  }

  return true;
}


void ofxLoopin::video::Video::renderBuffer( ofxLoopinBuffer * buffer ) {
  
  if ( !wasLoaded && engine->isLoaded() ) {
    ofxLoopinEvent event;
    event.type = "loaded";
    dispatch( event );
    wasLoaded = true;
  }

  if ( !engine->isLoaded() || engine->isPaused() ) {
    // std::cerr << "no delta "<< endl;
    renderingFrame.delta = 0;
  }

  clock.advance( renderingFrame );

  if ( !engine->isLoaded() ) 
    return;

  // videoSync();
  // engine->play();

  auto before = ofGetElapsedTimeMicros();
  engine->play();
  engine->update();
  auto after = ofGetElapsedTimeMicros();

//  clock.frame.time = engine->getTime();

  // if ( !engine->isFrameNew() )
  //   return;

  if ( buffer == nullptr )
    buffer = getBuffer( true );
  
  assert( buffer );

  ofRectangle bounds = ofRectangle( 0,0, engine->getWidth(), engine->getHeight() );
  buffer->defaultSize( bounds );

  ofTexture * tex = engine->getTexturePtr();

  // if ( tex != nullptr ) {
  //   cerr << "TEXTURE!!! :)" << endl;
  // }

  ofPixels & pixels = engine->getPixels();

  if ( !pixels.getWidth() || !pixels.getHeight() )
    return;

  if ( !buffer->begin() ) {
    return;
  }


  ofTexture texture;
  texture.allocate( pixels );
  // cerr << "Drawing " << bounds << endl;



  texture.draw( 0, 0, buffer->getWidth(), buffer->getHeight() );

  // player.draw( 0, 0, buffer->getWidth(), buffer->getHeight() );

  buffer->end();  
};
