#pragma once

//#include "interface/Blend.hpp"


#include "../control/Bool.hpp"
#include "../clock/Clock.hpp"
#include "../render/Render.hpp"
#include "../control/Enable.hpp"
#include "../control/Box.hpp"

#include "../interface/Blend.hpp"
#include "../interface/Clear.hpp"
#include "../shader/Shader.hpp"



#include "ofAppRunner.h"
#include "ofMatrix4x4.h"

/** loopin/type/layer/sub
shader:
  ref: shader

mesh:
  ref: mesh

camera :
  ref: camera

# src:
#   link: ../tex/src

transform:
  type: transform2D

aspect:
  type: float
  min: 0.1
  max: 2
*/

namespace ofxLoopin { namespace render {
class Blit : virtual public Render {
public:
  ofxLoopin::clock::Clock clockControl;
  ofxLoopin::control::Enable enable;
  ofxLoopin::control::Box box;
  ofxLoopin::interface::Clear clear;
  ofxLoopin::control::Enable advance;
  ofxLoopin::interface::Blend blend;


  void renderBuffer( ofxLoopin::base::Buffer * buffer );

protected:
  void addSubControls() {
    ofxLoopin::render::Render::addSubControls();
    addSubControl( "enable", &enable );
    addSubControl( "clear", &clear );
    addSubControl( "box", &box );
    addSubControl( "shader", &shader );

    addSubControl( "blend", &blend );

    if ( _needAdvance ) {
      advance.setEnumValue( control::ENABLE_NO );
      addSubControl( "advance", &advance );
    }

    if ( _needClock ) {
      addSubControl( "clock", &clockControl );
    }
  }

  virtual void renderClear( bool bufferIsNew = false );
  virtual bool renderSetup();
  virtual void renderSelf() {
    renderTexture();
  };
  virtual void renderStyle();

  virtual void renderBounds() {
    
  };
  virtual void renderAfter() {};

  virtual ofTexture * textureToRender() { return nullptr; };
  virtual void renderUniforms();
  void resetStyle();
  void resetUniforms();

  ofxLoopin::base::Buffer * _buffer = nullptr;
  ofxLoopin::shader::Shader * _shader = nullptr;

  bool _needAdvance = false;
  bool _needClock = false;


private:
};
}};