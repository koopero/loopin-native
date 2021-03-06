#pragma once

#include "../render/Render.hpp"
#include "../control/Enable.hpp"
#include "../control/Box.hpp"
#include "./PixelControl.hpp"


namespace ofxLoopin { namespace pixels {

class Render;

class Map : public ofxLoopin::render::Renders<Render> {};

class Render : public ofxLoopin::render::Render, virtual public Control  {
public:
  ofxLoopin::control::Enable input;
  ofxLoopin::control::Enable output;
  ofxLoopin::control::Bool replace;

  ofRectangle getBounds();

  void renderBuffer( ofxLoopin::base::Buffer * buffer ) override;
  void renderFloats( ofxLoopin::base::Buffer * buffer );

protected:
  bool _isDirty = false;
  int readWidth = -1;
  int readHeight = -1;

  // void updateLocal();
  // void patchLocal( const ofJson & value );
  // void patchString( string value );
  void dispatchData();

  void maybeOutputBuffer( ofxLoopin::base::Buffer * buffer );
  void addSubControls() {
    addPixelDataSubControls();
    input.setEnumValue( control::ENABLE_AUTO );
    addSubControl("input", &input );
    output.setEnumValue( control::ENABLE_NO );
    addSubControl("output", &output );
    addSubControl("box", &box );
    addSubControl("shader", &shader );
    addSubControl("buffer", &buffer );
  };

  static ofxLoopin::shader::Shader shader;
};



// end of namespace
}}
