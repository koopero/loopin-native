#pragma once

#include "../ofxLoopinControl.h"
#include "../options/BlendEquation.hpp"
#include "../options/BlendFunc.hpp"


namespace ofxLoopin { namespace interface {
class Blend : public ofxLoopinControl {
public:
  // Colour    colour;
  options::BlendEquation equation;
  options::BlendFunc srcRGB;
  options::BlendFunc dstRGB;
  options::BlendFunc srcAlpha;
  options::BlendFunc dstAlpha;

  void addSubControls() {
    addSubControl("equation", &equation );
    addSubControl("srcRGB", &srcRGB );
    addSubControl("srcAlpha", &srcAlpha );
    addSubControl("dstRGB", &dstRGB );
    addSubControl("dstAlpha", &dstAlpha );
  };

  void patchString( string str ) {
    std::string presetKey = str; 
    std::transform(presetKey.begin(), presetKey.end(), presetKey.begin(), ::tolower);

    if ( BLEND_PRESETS.count( presetKey ) ) {
      patch( BLEND_PRESETS[ presetKey ] );
    }
  };

  void apply() {
    // glBlendColor( colour.r, colour.g, colour.b, colour.a );
    if ( (GLenum) equation == GL_NONE ) {
      glDisable( GL_BLEND );
    } else {
      glEnable( GL_BLEND );
      glBlendEquation( equation );
      glBlendFuncSeparate( srcRGB, dstRGB, srcAlpha, dstAlpha );
      // glBlendFuncSeparate( GL_ONE, GL_ONE, GL_ONE, GL_ONE );
    }

  }
protected:
  static const ofJson BLEND_PRESETS;
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
