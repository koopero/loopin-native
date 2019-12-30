#pragma once

#include "ofGraphics.h"

#include "../control/Control.hpp"
#include "../control/Event.hpp"
#include "../clock/Frame.hpp"
#include "../control/Map.hpp"
#include "../control/Reference.hpp"
#include "../shader/Shaders.hpp"
#include "../shader/Uniforms.hpp"

/** loopin/root/render/:
  map: layer
*/

namespace ofxLoopin { namespace render {
class Render : virtual public ofxLoopin::control::Control {
public:
  ofxLoopin::control::Reference<ofxLoopin::base::Buffer,ofxLoopin::base::HasBuffers> buffer;

  int iterations = 1;
  bool clear = true;

  virtual void renderReset() {
    
  };

  virtual void render( const ofxLoopin::clock::Frame & frame, ofxLoopin::base::Buffer * _buffer = nullptr ) {
    if ( frame == lastFrame )
      return;

    renderingFrame = frame;
    renderingBuffer = _buffer != nullptr ? _buffer : getBuffer( _createBuffer );

    renderBuffer( renderingBuffer );

    renderingBuffer = nullptr;
  };

  virtual void renderBuffer( ofxLoopin::base::Buffer * buffer ) {
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


  ofxLoopin::clock::Frame renderingFrame;
  ofxLoopin::base::Buffer * renderingBuffer;
  ofxLoopin::clock::Frame lastFrame;


  void addSubControls() {
    addSubControl("buffer", &buffer );
    addSubControl( &uniforms );
    addSubControl( "shader", &shader );
  };

  ofxLoopin::shader::UniformSet uniforms;
  ofxLoopin::control::Reference<ofxLoopin::shader::ShaderWithUniforms,ofxLoopin::shader::HasShaders> shader;

  virtual ofxLoopin::base::Buffer * getBuffer( bool create = false ) {
    if ( buffer.key.size() )
      return getBuffer( buffer.key, create );

    return getBuffer( key, create );
  }

  ofxLoopin::base::Buffer * getBuffer( const string & key, bool create = false );

  static ofxLoopin::shader::Shader shaderDefault; 
};

class RenderList {
public:
  virtual void render( const ofxLoopin::clock::Frame & frame, ofxLoopin::base::Buffer * _buffer = nullptr ) {};
};


template <class Render>
class Renders : public ofxLoopin::control::Map<Render>, public RenderList {
public:
  void render( const ofxLoopin::clock::Frame & frame, ofxLoopin::base::Buffer * _buffer = nullptr ) {
    for( auto it = ofxLoopin::control::Map<Render>::_map.begin(); it != ofxLoopin::control::Map<Render>::_map.end(); it++) {
      Render &render = it->second;
      string key = it->first;
      render.render( frame, _buffer );
    }
  }
};


template <class Render>
class OrderedRenders : public ofxLoopin::control::Map<Render>, public RenderList {
public:
  void render( const ofxLoopin::clock::Frame & frame, ofxLoopin::base::Buffer * _buffer = nullptr ) {

    std::vector<Render*> list;
    for( auto it = ofxLoopin::control::Map<Render>::_map.begin(); it != ofxLoopin::control::Map<Render>::_map.end(); it++) {
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
}};