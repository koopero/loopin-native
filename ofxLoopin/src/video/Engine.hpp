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
  int getFrames() const;
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
};

}};