#pragma once

#include "../render/Render.hpp"
#include "../control/Enable.hpp"
#include "../control/Box.hpp"
#include "./Control.hpp"


namespace ofxLoopin { namespace pixels {

class Render;

class Map : public ofxLoopin::render::Renders<Render> {};

class Render : public ofxLoopin::render::Render, virtual public Control  {
public:
  ofxLoopin::control::Enable input;
  ofxLoopin::control::Enable output;
  ofxLoopin::control::Box box;
  ofxLoopin::control::Bool replace;

  ofRectangle getBounds();

  void renderBuffer( ofxLoopin::base::Buffer * buffer );

protected:
  bool _isDirty = false;

  void updateLocal();
  void patchLocal( const ofJson & value );
  void patchString( string value );
  void dispatchData();

  void maybeOutputBuffer( ofxLoopin::base::Buffer * buffer );
  void addSubControls() {
    addPixelDataSubControls();
    addSubControl("input", &input );
    addSubControl("output", &output );
    addSubControl("box", &box );
    addSubControl("shader", &shader );
    addSubControl("buffer", &buffer );
  };

  static ofxLoopin::shader::Shader shader;
};



// end of namespace
}}
