#pragma once

#include "../control/Control.hpp"
#include "../control/Colour.hpp"
#include "../options/BlendEquation.hpp"
#include "../options/BlendFunc.hpp"

#include "ofMain.h"


namespace ofxLoopin { namespace interface {
class Blend : virtual public ofxLoopin::control::Control {
public:
  control::Colour colour;
  options::BlendEquation equation;
  options::BlendFunc srcRGB;
  options::BlendFunc dstRGB;
  options::BlendFunc srcAlpha;
  options::BlendFunc dstAlpha;

  void addSubControls() override {
    addSubControl("colour", &colour );
    addSubControl("equation", &equation );
    addSubControl("srcRGB", &srcRGB );
    addSubControl("srcAlpha", &srcAlpha );
    addSubControl("dstRGB", &dstRGB );
    addSubControl("dstAlpha", &dstAlpha );
  };

  void apply() {

    if ( (GLenum) equation == GL_NONE ) {
      // std::cerr << "blendApply-none" << std::endl;
      ofDisableBlendMode();
      glDisable( GL_BLEND );
    } else {
      glEnable( GL_BLEND );
      glBlendEquation( equation );
      // std::cerr << "blendApply " << equation << std::endl;

      glBlendFuncSeparate( srcRGB, dstRGB, srcAlpha, dstAlpha );
      glBlendColor( colour.getAxis(0), colour.getAxis(1), colour.getAxis(2), colour.getAxis(3) );
      // std::cerr << "apply colour " << colour.getAxis(0) << "," << colour.getAxis(1) << "," << colour.getAxis(2) << "," << colour.getAxis(3) << std::endl;
    }
  };
  
protected:
  static const ofJson BLEND_PRESETS;

  void patchString( string str ) override {
    patchPreset( str );
  };

  void patchLocal( const ofJson & value ) override {
    if ( value.is_object() && value.count("preset") && value["preset"].is_string() ) {
      patchPreset( value["preset"].get<std::string>() );
    }
  };

  void patchPreset( string str ) {

    std::string presetKey = str; 
    std::transform(presetKey.begin(), presetKey.end(), presetKey.begin(), ::tolower);

    if ( BLEND_PRESETS.count( presetKey ) ) {
      patch( BLEND_PRESETS[ presetKey ] );
    }
  };

};
} }
