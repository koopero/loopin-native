#pragma once

#include "./VideoClock.hpp"
#include "../ofxLoopinBuffer.h"

namespace ofxLoopin { namespace video {

template <class Player>
class Engine {
public:
  void load( string file );
  void play();
  void pause();

  double getTime() const;
  double getTime( int frame ) const ;
  float getPosition() const;
  double getDuration() const;
  double getFrameRate() const {
    return float( getTotalNumFrames() ) / getDuration();
  };

  int getCurrentFrame() const {
    return player.getCurrentFrame();
  };
  int getTotalNumFrames() const;
  ofRectangle getBounds() const { return ofRectangle( 0,0, player.getWidth(), player.getHeight() ); };
  void setSpeed( float speed );
  void setPlaying( bool playing );
  bool isReady() const;
  bool isFrameNew();
  bool isPaused() const;
  bool isLoaded() const;
  bool isLoading() const;
  bool isSeeking() const;
  bool isPlaying() const;
  bool getIsMovieDone() const { return player.getIsMovieDone(); };
  void nextFrame();
  void setFrame(int frame);
  void drawToBuffer( ofxLoopinBuffer * buffer );
  void update() { player.update(); };
  void draw(float x, float y, float w, float h) { player.draw( x,y,w,h ); };


  void loadClock( VideoClock & clock ) {
    clock.duration = getDuration();
    clock.rate = getFrameRate();
  };

  void updateClock( VideoClock & clock ) {
    clock.frame.time = getTime();
    clock.index = getCurrentFrame();
    // cerr << "engine.updateClock " << clock.index  << endl;
  };
protected:
  Player player;
};

}};


template <class Player>
void ofxLoopin::video::Engine<Player>::load( string file ) {
  player.setUseTexture( true );
  // player.setPixelFormat( OF_PIXELS_RGB );
  player.load( file );
  player.play();
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
int ofxLoopin::video::Engine<Player>::getTotalNumFrames() const {
  return player.getTotalNumFrames();
}

template <class Player>
double ofxLoopin::video::Engine<Player>::getDuration() const {
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
  // cerr << "player.setFrame " << frame << endl;
  player.setFrame( frame );
}

