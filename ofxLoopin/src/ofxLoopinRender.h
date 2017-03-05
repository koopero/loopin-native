#pragma once

#include "ofGraphics.h"

#include "ofxLoopinControl.h"
#include "ofxLoopinEvent.h"
#include "ofxLoopinFrame.h"
#include "ofxLoopinMap.h"
#include "ofxLoopinRef.h"
#include "ofxLoopinShaders.h"
#include "ofxLoopinUniforms.h"

/** loopin/root/render/:
  map: layer
*/

class ofxLoopinRender : public ofxLoopinControl {
public:
  ofxLoopinRef<ofxLoopinBuffer,ofxLoopinHasBuffers> buffer;

  int iterations = 1;
  bool clear = true;

  virtual void render( const ofxLoopinFrame & frame, ofxLoopinBuffer * _buffer = nullptr ) {
    if ( frame == lastFrame )
      return;

    renderingFrame = frame;
    renderingBuffer = _buffer != nullptr ? _buffer : getBuffer( _createBuffer );

    renderBuffer( renderingBuffer );

    renderingBuffer = nullptr;
  };

  virtual void renderBuffer( ofxLoopinBuffer * buffer ) {
    if ( !buffer )
      return;

    buffer->defaultSize( getBounds() );

    if ( !buffer->begin() )
      return;

    if ( clear ) {
      ofClear( 0, 0, 0, 0 );
    }

    draw( buffer->getArea() );
    buffer->end();
  }

  virtual void draw( const ofRectangle & area ) {};

  virtual ofRectangle getBounds() {

  };

protected:

  bool _createBuffer = true;


  ofxLoopinFrame renderingFrame;
  ofxLoopinBuffer * renderingBuffer;
  ofxLoopinFrame lastFrame;


  void addSubControls() {
    addSubControl("buffer", &buffer );
    addSubControl( &uniforms );
    addSubControl( "shader", &shader );
  };

  ofxLoopinUniformSet uniforms;
  ofxLoopinRef<ofxLoopinShaderWithUniforms,ofxLoopinHasShaders> shader;

  virtual ofxLoopinBuffer * getBuffer( bool create = false ) {
    if ( buffer.key.size() )
      return getBuffer( buffer.key, create );

    return getBuffer( key, create );
  }

  ofxLoopinBuffer * getBuffer( const string & key, bool create = false );
};

class ofxLoopinRenderList {
public:
  virtual void render( const ofxLoopinFrame & frame, ofxLoopinBuffer * _buffer = nullptr ) {};
};


template <class Render>
class ofxLoopinRenders : public ofxLoopinMap<Render>, public ofxLoopinRenderList {
public:
  void render( const ofxLoopinFrame & frame, ofxLoopinBuffer * _buffer = nullptr ) {
    for( auto it = ofxLoopinMap<Render>::_map.begin(); it != ofxLoopinMap<Render>::_map.end(); it++) {
      Render &render = it->second;
      string key = it->first;
      render.render( frame, _buffer );
    }
  }
};
