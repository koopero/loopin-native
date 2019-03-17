#pragma once

#include "../ofxLoopinControl.h"
#include "../type/Colour.hpp"
#include "../options/BlendEquation.hpp"
#include "../options/BlendFunc.hpp"


namespace ofxLoopin { namespace interface {
class Blend : public ofxLoopinControl {
public:
  type::Colour colour;
  options::BlendEquation equation;
  options::BlendFunc srcRGB;
  options::BlendFunc dstRGB;
  options::BlendFunc srcAlpha;
  options::BlendFunc dstAlpha;

  void addSubControls() {
    addSubControl("colour", &colour );
    addSubControl("equation", &equation );
    addSubControl("srcRGB", &srcRGB );
    addSubControl("srcAlpha", &srcAlpha );
    addSubControl("dstRGB", &dstRGB );
    addSubControl("dstAlpha", &dstAlpha );
  };

  void apply() {
    if ( (GLenum) equation == GL_NONE ) {
      glDisable( GL_BLEND );
    } else {
      glEnable( GL_BLEND );
      glBlendEquation( equation );
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

    /** loopin/type/layer/sub/blend
      options:
        - none
        - alpha
        - add
        - subtract
        - multiply
        - screen
    */
    // blend.setEnumKey("none", OF_BLENDMODE_DISABLED );
    // blend.setEnumKey("alpha", OF_BLENDMODE_ALPHA );
    // blend.setEnumKey("add", OF_BLENDMODE_ADD );
    // blend.setEnumKey("subtract", OF_BLENDMODE_SUBTRACT );
    // blend.setEnumKey("multiply", OF_BLENDMODE_MULTIPLY );
    // blend.setEnumKey("screen", OF_BLENDMODE_SCREEN );
