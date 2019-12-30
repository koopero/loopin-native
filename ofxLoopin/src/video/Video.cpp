#include "./Video.hpp"

void ofxLoopin::video::Video::patchLocalAfter( const ofJson & value ) {
  if ( file.hasChanged() ) {
    loadFile ();
  }
};

void ofxLoopin::video::Video::loadFile() {
  string absPath = file.fileAbsolute();
  control::Event event;


  wasLoaded = false;
  if ( absPath.size() ) {

    event.type = "captureStart";
    dispatch( event );

    engine->load( absPath );

    event.type = "captureEnd";
    dispatch( event );

  } else {
    event.type = "error";
    dispatch( event );
  }
};


void ofxLoopin::video::Video::patchString( string value ) {
  file.patch( value );
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
  bool frameIsNew = engine->isFrameNew();
  bool shouldDraw = frameIsNew;


  if ( shouldDraw ) {
    ofRectangle bounds = engine->getBounds();
    buffer->defaultSize( bounds );

    if ( buffer->begin() ) {
      engine->draw( 0, 0, buffer->getWidth(), buffer->getHeight() );
      buffer->end();  

      if ( !wasLoaded && engine->isLoaded() ) {
        onLoaded();
      }
    }
  } else if ( !clock.ignoreStale() ) {
    return;
  }

  engine->updateClock( clock );
  sendSyncEvent = sendSyncEvent || clock.checkEnd();

  if ( sendSyncEvent ) {
    control::Event event;
    event.type = "sync";
    event.data["clock"] = clock.read();
    dispatch( event );    
    sendSyncEvent = false;
  }



  // if ( isDone ) {
  //   control::Event event;
  //   event.type = "ended";
  //   event.data["clock"] = clock.read();
  //   dispatch( event );    
  // }
};
