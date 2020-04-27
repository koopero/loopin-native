#include "./Saver.hpp"
#include "../base/File.hpp"

void ofxLoopin::image::Saver::patchLocal( const ofJson & value ) {
  // std::cerr << "ofxLoopin::image::Saver::patchLocal " << value << endl;
  if (
    value.is_object()
    && value.count( "dest" )
    && value["dest"].is_string()
    && !value.count( "iterations" )
  ) {
    // std::cerr << "ofxLoopin::image::Saver::patchLocal" << endl;
    iterations = iterations ? iterations : 1;
    // iterations = 1;
  }
}



void ofxLoopin::image::Saver::patchString( string value ) {
  dest = value;
  iterations = iterations > 0 ? iterations : 1;
  // iterations = 1;
}

void ofxLoopin::image::Saver::updateLocal( ) {
  if ( thread ) {
    for( ofxLoopin::control::Event &event : thread->flushEvents() ) {
      dispatch( event );
    }
  }
}

void ofxLoopin::image::Saver::renderBuffer( ofxLoopin::base::Buffer * buffer ) {
  if ( !iterations )
    return;

  iterations --;

  ofxLoopin::control::Event event;
  event.data["dest"] = dest;
  event.data["quality"] = quality.getKey();


  if ( !buffer || !buffer->isAllocated() ) {
    event.type = "error";
    event.data["error"] = "buffer not allocated";
    dispatch( event );
    return;
  }

  if ( !thread ) {
    thread = new ofxLoopin::image::SaverThread();
  }

  string destAbs = ofxLoopin::base::File::target( dest );

  ofPixels pixels;
  ofFbo &fbo = buffer->getFbo();

  fbo.readToPixels( pixels );

  switch ( format.getEnumValue() ) {
    case OF_IMAGE_FORMAT_JPEG:
      pixels.setNumChannels( 3 );
    break;

    default:
    break;
  }

  event.data["frame"] = renderingFrame.index;
  event.data["format"] = format.getKey();
  event.data["quality"] = quality.getKey();

  thread->save( destAbs, pixels, event, format.getEnumValue(), quality.getEnumValue() );

}


void ofxLoopin::image::SaverThread::save(
  const string & dest,
  ofPixels data,
  ofxLoopin::control::Event event,
  ofImageFormat format,
  ofImageQualityType qualityLevel
) {
  lock();
  dest_ = dest;
  data_ = data;
  event_ = event;
  format_ = format;
  qualityLevel_ = qualityLevel_;
  unlock();

  if ( !isThreadRunning() ) {
    startThread();
  }
}

void ofxLoopin::image::SaverThread::threadedFunction() {
  while( isThreadRunning() ) {
    lock();
    string dest = dest_;
    ofPixels data = data_;
    ofImageFormat format = format_;
    ofImageQualityType qualityLevel = qualityLevel_;
    ofxLoopin::control::Event event = event_;

    dest_ = "";
    unlock();


    event.data["dest"] = dest;

    ofBuffer buffer;
    ofSaveImage( data, buffer, format, qualityLevel );
    ofBufferToFile( dest, buffer, true );

    event.type = "save";

    lock();
    events_.push_back( event );
    bool keepRunning = !!dest_.size();
    unlock();


    if ( !keepRunning ) {
      stopThread();
    }
  }

}

std::vector<ofxLoopin::control::Event> ofxLoopin::image::SaverThread::flushEvents() {
  lock();
  std::vector<ofxLoopin::control::Event> result = events_;
  events_.resize(0);
  unlock();

  return result;
}

//

//
