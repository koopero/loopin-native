#pragma once

#include "ofGraphics.h"

#include "./control/Control.hpp"
#include "./control/Event.hpp"
#include "ofxLoopinFrame.h"
#include "ofxLoopinMap.h"
#include "ofxLoopinRef.h"
#include "./shader/Shaders.hpp"
#include "ofxLoopinUniforms.h"

/** loopin/root/render/:
  map: layer
*/

class ofxLoopinRender : public ofxLoopin::control::Control {
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
    return ofRectangle(0,0,0,0);
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
  ofxLoopinRef<ofxLoopin::shader::ShaderWithUniforms,ofxLoopin::shader::HasShaders> shader;

  virtual ofxLoopinBuffer * getBuffer( bool create = false ) {
    if ( buffer.key.size() )
      return getBuffer( buffer.key, create );

    return getBuffer( key, create );
  }

  ofxLoopinBuffer * getBuffer( const string & key, bool create = false );

  static ofxLoopin::shader::Shader shaderDefault; 
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


template <class Render>
class ofxLoopinOrderedRenders : public ofxLoopinMap<Render>, public ofxLoopinRenderList {
public:
  void render( const ofxLoopinFrame & frame, ofxLoopinBuffer * _buffer = nullptr ) {

    std::vector<Render*> list;
    for( auto it = ofxLoopinMap<Render>::_map.begin(); it != ofxLoopinMap<Render>::_map.end(); it++) {
      list.push_back( &it->second );
    }

    if ( !list.size() )
      return;

    std::stable_sort( list.begin(), list.end(), compareRenderOrder );

    // std::cerr << "render order " << std::endl;

    for ( auto it=list.begin(); it!=list.end(); ++it) {
      Render *render = *it;
      // std::cerr << "order " << (float)render->order << std::endl;
      render->render( frame, _buffer );
    }
  }

private:
  static bool compareRenderOrder( Render * a, Render * b ) {
    return ((float)(a->order.getValueFloat()) < (float)(b->order.getValueFloat()));
  }

};
