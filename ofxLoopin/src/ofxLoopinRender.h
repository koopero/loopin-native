#pragma once

#include "ofGraphics.h"

#include "ofxLoopinControl.h"
#include "ofxLoopinEvent.h"
#include "ofxLoopinFrame.h"
#include "ofxLoopinMap.h"
#include "ofxLoopinRef.h"
#include "ofxLoopinShaders.h"
#include "ofxLoopinUniforms.h"


class ofxLoopinRender : public ofxLoopinControl {
public:
  int iterations = 1;
  bool clear = true;

  virtual void render( ofxLoopinBuffer * buffer = nullptr ) {

    if ( !buffer )
      buffer = getBuffer( true );

    buffer->defaultSize( getBounds() );

    if ( buffer->begin() ) {
      // ofxLoopinEvent e = ofxLoopinEvent("rendering");
      // dispatch( e );

      if ( clear ) {
        ofClear( 0, 0, 0, 0 );
      }
      draw( buffer->getArea() );
      buffer->end();
    }
  };
  virtual void draw( const ofRectangle & area ) {};

  virtual ofRectangle getBounds() {

  };

protected:
  void addSubControls() {
    addSubControl( &uniforms );
    addSubControl( "shader", &shader );
  };

  ofxLoopinUniformSet uniforms;
  ofxLoopinRef<ofxLoopinShaderWithUniforms,ofxLoopinHasShaders> shader;

  virtual ofxLoopinBuffer * getBuffer( bool create = false ) {
    return getBuffer( key, create );
  }

  ofxLoopinBuffer * getBuffer( const string & key, bool create = false );
};

class ofxLoopinRenderList {
public:
  virtual void render( ofxLoopinBuffer * buffer = nullptr ) {};
};


template <class Render>
class ofxLoopinRenders : public ofxLoopinMap<Render>, public ofxLoopinRenderList {
public:
  void render( ofxLoopinBuffer * buffer = nullptr ) {
    for( auto it = ofxLoopinMap<Render>::_map.begin(); it != ofxLoopinMap<Render>::_map.end(); it++) {
      Render &render = it->second;
      string key = it->first;
      render.render( buffer );
    }
  }
};
