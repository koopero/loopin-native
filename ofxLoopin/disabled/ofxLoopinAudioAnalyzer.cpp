#include "ofxLoopinAudioAnalyzer.h"

void ofxLoopinAudioAnalyzer::audioIn( ofSoundBuffer &buffer ) {

  unsigned int sampleRate = buffer.getSampleRate();
  if ( sampleRate != audioAnalyzer.getSampleRate() ) {
    audioAnalyzer.reset( sampleRate, 512, 1 );
    audioAnalyzer.setActive( 0, SPECTRUM, true );
  }

  audioAnalyzer.analyze( buffer );
}

void ofxLoopinAudioAnalyzer::renderBuffer( ofxLoopin::base::Buffer * buffer ) {
  // Ensure the soundstream is running
  if ( !streamIsOpen ) {
    soundStream.printDeviceList();
    soundStream.setInput( *this );
    streamIsOpen = soundStream.setup( 0, 1, 44100, 256, 1 );
  }

  if ( !buffer )
    buffer = getBuffer( true );

  buffer->defaultSize( getBounds() );

  if ( !buffer->begin() ) {
    // TODO: Error here
    return;
  }




  ofImage output;
  output.allocate( 64, 4, OF_IMAGE_COLOR );
  output.setColor( ofColor(0,0,255,255));

  ofPixels &pixels = output.getPixels();

  output.update();
  output.draw(0,0);
  buffer->end();
}

ofRectangle ofxLoopinAudioAnalyzer::getBounds() {
  return ofRectangle( 0, 0, 1, 64 );
}
