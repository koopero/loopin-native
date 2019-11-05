#include "./Video.hpp"

void ofxLoopin::video::Video::patchLocal( const ofJson & value ) {
  // std::cerr << "ofxLoopin::video::Video::patchLocal " << value << endl;

  if ( value.is_object() && value.count("file") && value["file"].is_string() ) {
    loadFile ( value["file"].get<std::string>() );
  }

  // std::cerr << "ofxLoopin::video::Video::patchLocal after " << endl;
};

void ofxLoopin::video::Video::loadFile( const string & file ) {
  string videoPath = file;
  string absPath = ofxLoopin::base::File::find( videoPath );

  wasLoaded = false;
  if ( absPath.size() ) {
    engine->load( absPath );
  } else {
    control::Event event;
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
  control::Event event;
  event.type = "loaded";
  dispatch( event );
  wasLoaded = true;
}

void ofxLoopin::video::Video::renderBuffer( base::Buffer * buffer ) {
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
    case ofxLoopin::clock::Frame::Mode::STEP:
      engine->setSpeed(0);
      if ( clock.frame.delta && !sendSyncEvent ) {
        // cerr << "next Frame " << endl;
        engine->nextFrame();
      }
    break;

    case ofxLoopin::clock::Frame::Mode::TIME:
      engine->setSpeed( clock.frame.speed );
    break;

    case ofxLoopin::clock::Frame::Mode::FRAME:
      engine->setSpeed(0);
      engine->nextFrame();
    break;

    default:
    case ofxLoopin::clock::Frame::Mode::STOP:
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
    control::Event event;
    event.type = "sync";
    dispatch( event );    
    sendSyncEvent = false;
  }

  if ( engine->getIsMovieDone() ) {
    control::Event event;
    event.type = "ended";
    dispatch( event );    
  }
};
