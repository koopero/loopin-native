#pragma once

#include "../control/Colour.hpp"
#include "../control/Enable.hpp"



namespace ofxLoopin { namespace interface {
class Clear : public ofxLoopin::control::Control {
public:
  control::Colour colour;
  control::Enable enable;
  control::Enable depth;

  void addSubControls() override {
    addSubControl("colour", &colour );
    addSubControlAlias("color", &colour );

    enable.setEnumValue( control::ENABLE_AUTO );
    addSubControl("enable", &enable );

    depth.setEnumValue( control::ENABLE_AUTO );
    addSubControl("depth", &depth );

  };

  bool shouldClear( bool bufferIsNew = false ) {
    bool clear = enable.isEnabledOnce( bufferIsNew );
    _clearColour = clear;
    _clearDepth = depth.isEnabledOnce( clear );

    return _clearDepth || _clearColour;
  }

  void renderClear() {
    if ( _clearColour ) {
      ofDisableBlendMode();
      ofClear( colour.asFloatColor() );
    }

    if ( _clearDepth ) {
      #ifndef TARGET_OPENGLES
        glClearDepth( 1 );
      #endif
    }
  };

private:
  bool _clearColour = false;
  bool _clearDepth = false;


protected:
  void patchLocal( const ofJson & val ) override {
    if ( val.is_boolean() )
      enable.patch( val );
  };

};
} }
