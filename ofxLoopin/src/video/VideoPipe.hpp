#pragma once

#include "../render/Render.hpp"

#include "ofThread.h"

namespace ofxLoopin { namespace video {

class PipeConfig {
  public:
    std::string command;
    unsigned int width;
    unsigned int height; 
    bool shouldRead;
    bool shouldWrite;

    size_t getSize() {
      return width * height * 3;
    };

    bool operator==(const PipeConfig &other) const {
      return command == other.command 
        && width == other.width 
        && height == other.height 
        && shouldRead == other.shouldRead 
        && shouldWrite == other.shouldWrite;
    };

    bool operator!=(const PipeConfig &other) const {
      return !(*this == other);
    };

}

class PipeThread : public ofThread {
public :
  bool shouldRead

  void injestFrame( ofFloatPixels pixels );
  void setOutputFrame( ofPixels &frame );
  ofPixels & getInputFrame();

  void threadedFunction() override {

    while( isThreadRunning() ) {
      iteratePipe();
    }

    cleanup();
  }

  void iteratePipe() {
    bool shouldRun = false;
    bool shouldRestart = false;

    lock();
    if ( config != nextConfig ) {
      shouldRestart = true; 
      config = nextConfig; 
    }
    unlock();

  
    if ( !shouldRun() )
      continue;

    if ( !commandIsRunning() ) {
      runCommand();
      continue;
    } 
  }

  void runCommand() {
    std::string cmd = buildCommand();
    proc = bp::child( cmd, bp::std_out > istream, bp::std_err > estream, bp::std_in < ostream );
  }
  
  void sendFrame() {
    ofPixels frame;

    

    ostream.write( frame.getData(), config.getSize() );
  }

  void cleanup() {

  }

  void setConfig( PipeConfig config ) {
    lock();
    nextConfig = config;
    unlock();
  }

protected:
  ofPixels inputFrame;
  ofPixels outputFrame;
  PipeConfig config;
  PipeConfig nextConfig;
  bp::child proc;
  bp::ipstream istream;
  bp::ipstream estream;
  bp::opstream ostream;
}

class VideoPipe : public ofxLoopin::render::Render {
public:
  control::Enable enable;
  control::String command;
  control::Box box;

protected:
  PipeThread worker;

  void addSubControls() override {
    addSubControl( "enable", &enable );
    addSubControl( "command", &command  );
    addSubControl( "box", &box  );
  }


  void updatePipe() {
    worker.setConfig( config );
  }
};

}}