#include "./Engine.hpp"

template <class Player>
double ofxLoopin::video::Engine<Player>::getTime() {
  return getTime( player.getCurrentFrame() );
}

template <class Player>
double ofxLoopin::video::Engine<Player>::getTime( int frame ) {
  float duration = player.getDuration();
  float position = player.getPosition();

  double time = position * duration;

  return time;
}

template <class Player>
int ofxLoopin::video::Engine<Player>::getFrames() {
  return player.getTotalNumFrames();
}

template <class Player>
double ofxLoopin::video::Engine<Player>::getDuration() {
  return player.getDuration();
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
    player.pause();
  }
}

template <class Player>
bool ofxLoopin::video::Engine<Player>::isReady() const {
  return player.isLoaded();
}


template <class Player>
void ofxLoopin::video::Engine<Player>::drawToBuffer( ofxLoopinBuffer * buffer ) {
  ofRectangle bounds = ofRectangle( 0,0, player.getWidth(), player.getHeight() );
  buffer->defaultSize( bounds );

  if ( !buffer->begin() ) {
    // TODO: Error here
    return;
  }


  player.draw( 0, 0, buffer->getWidth(), buffer->getHeight() );

  buffer->end();  
}