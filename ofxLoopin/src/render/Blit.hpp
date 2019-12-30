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
    advance.setEnumValue( control::ENABLE_NO );
    addSubControl( "advance", &advance );
    addSubControl( "shader", &shader );
    addSubControl( "clock", &clockControl );
    addSubControl( "blend", &blend );
  }

  virtual void renderClear();
  virtual bool renderSetup();
  virtual void renderSelf() {};
  virtual void renderUniforms();

  ofxLoopin::base::Buffer * _buffer = nullptr;
  ofxLoopin::shader::Shader * _shader = nullptr;

private:
};
}};