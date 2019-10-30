#pragma once

#include "../ofxLoopinBuffer.h"

namespace ofxLoopin { namespace video {

template <class Player>
class Engine {
public:
  void update();

  void load( string file );
  void play();
  void pause();

  double getTime() const;
  double getTime( int frame ) const ;
  float getPosition() const;
  int getCurrentFrame() const;
  int getTotalNumFrames() const;
  double getDuration();
  void setSpeed( float speed );
  void setPlaying( bool playing );
  bool isReady() const;
  bool isFrameNew();
  bool isPaused() const;
  bool isLoaded() const;
  bool isLoading() const;
  bool isSeeking() const;
  bool isPlaying() const;

  void nextFrame();
  void setFrame(int frame);
  void drawToBuffer( ofxLoopinBuffer * buffer );
protected:
  Player player;
  bool hasDuration;
};

}};



template <class Player>
void ofxLoopin::video::Engine<Player>::update() {
  player.update();
}

template <class Player>
void ofxLoopin::video::Engine<Player>::load( string file ) {
  // player.setUseTexture( true );
  player.setPixelFormat( OF_PIXELS_RGB );
  // player.loadAsync( file );
  // player.initTextureCache();
  ofSetLogLevel(OF_LOG_VERBOSE);
  // std::cerr << "VIDEO LOAD " << file << std::endl;
  player.load( file );
  // player.stop();
}

template <class Player>
void ofxLoopin::video::Engine<Player>::play() {
  player.play();
}

template <class Player>
void ofxLoopin::video::Engine<Player>::pause() {
  player.stop();
}

template <class Player>
double ofxLoopin::video::Engine<Player>::getTime() const {
  return getTime( player.getCurrentFrame() );
}

template <class Player>
double ofxLoopin::video::Engine<Player>::getTime( int frame ) const  {
  float duration = player.getDuration();
  float position = player.getPosition();

  double time = position * duration;

  return time;
}

template <class Player>
float ofxLoopin::video::Engine<Player>::getPosition() const {
  // TODO
  return 0;
}

template <class Player>
int ofxLoopin::video::Engine<Player>::getCurrentFrame() const {
  // TODO
  return 0;
}

template <class Player>
int ofxLoopin::video::Engine<Player>::getTotalNumFrames() const {
  return player.getTotalNumFrames();
}

template <class Player>
double ofxLoopin::video::Engine<Player>::getDuration() {
  if ( hasDuration )
    return player.getDuration();

  return 0;
}

template <class Player>
void ofxLoopin::video::Engine<Player>::setSpeed( float speed ) {
  player.setSpeed( speed );
}

template <class Player>
void ofxLoopin::video::Engine<Player>::setPlaying( bool playing ) {
  if ( playing ) {
    player.play();
  } else {
    player.stop();
  }
}

template <class Player>
bool ofxLoopin::video::Engine<Player>::isReady() const {
  return player.isLoaded();
}


template <class Player>
bool ofxLoopin::video::Engine<Player>::isFrameNew() {
  return player.isFrameNew();
}

template <class Player>
bool ofxLoopin::video::Engine<Player>::isPaused() const {
  return player.isPaused();  
}

template <class Player>
bool ofxLoopin::video::Engine<Player>::isLoaded() const {
  return player.isLoaded();
}

template <class Player>
bool ofxLoopin::video::Engine<Player>::isLoading() const {
  return player.isLoading();
}

template <class Player>
bool ofxLoopin::video::Engine<Player>::isSeeking() const {
  return player.isSeeking();
}

template <class Player>
bool ofxLoopin::video::Engine<Player>::isPlaying() const {
  return player.isPlaying();
}

template <class Player>
void ofxLoopin::video::Engine<Player>::nextFrame() {
  return player.nextFrame();
}

template <class Player>
void ofxLoopin::video::Engine<Player>::setFrame(int frame) {

}

template <class Player>
void ofxLoopin::video::Engine<Player>::drawToBuffer( ofxLoopinBuffer * buffer ) {
  ofRectangle bounds = ofRectangle( 0,0, player.getWidth(), player.getHeight() );
  buffer->defaultSize( bounds );

  ofTexture * tex = player.getTexturePtr();

  if ( tex != nullptr ) {
    // cerr << "TEXTURE!!! :)" << endl;
  }

  // ofPixels & pixels = player.getPixels();

  // if ( !pixels.getWidth() || !pixels.getHeight() )
  //   return;

  if ( !buffer->begin() ) {
    return;
  }


  // ofTexture texture;
  // texture.allocate( pixels );
  // // cerr << "Drawing " << bounds << endl;



  tex->draw( 0, 0, buffer->getWidth(), buffer->getHeight() );

  // // player.draw( 0, 0, buffer->getWidth(), buffer->getHeight() );

  buffer->end();  
}