#pragma once

#include "./control/Control.hpp"
#include "ofxLoopin::control::Number.h"

#include "ofMatrix4x4.h"

/** loopin/type/transform2D/sub:
  x/type: float
  y/type: float
  aspect/type: float
  scale/type: float
  rotate/type: float
  mode/options:
    - cover
    - contain

*/

enum ofxLoopinTransform2DMode {
  COVER, CONTAIN
 };

class ofxLoopinTransform2D : public ofxLoopin::control::Control {
public:
  ofxLoopin::control::Number x;
  ofxLoopin::control::Number y;
  ofxLoopin::control::Number aspect = ofxLoopin::control::Number(1);
  ofxLoopin::control::Number scale = ofxLoopin::control::Number(1);
  ofxLoopin::control::Number rotate;
  ofxLoopin::control::Enum<ofxLoopinTransform2DMode,ofxLoopinTransform2DMode::COVER> mode;

  ofMatrix4x4 makeMatrix ( float layerAspect, float bufferAspect ) const  {
    // std::cerr << "transform2D::layerAspect " << layerAspect << endl;
    // std::cerr << "transform2D::bufferAspect " << bufferAspect << endl;

    ofMatrix4x4 mat;
    float ourAspect = aspect;
    float scale = ofxLoopinTransform2D::scale;

    switch ( mode.getEnumValue() ) {
      case ofxLoopinTransform2DMode::COVER:
        if ( fabs(layerAspect) < fabs(bufferAspect) ) {
          scale *= bufferAspect / layerAspect;
        }
      break;

      case ofxLoopinTransform2DMode::CONTAIN:
        if ( fabs(layerAspect) > fabs(bufferAspect) ) {
          scale /= layerAspect / bufferAspect;
        }
      break;
    }


    mat.scale( scale, scale, 1 );

    mat.scale( bufferAspect, 1, 1 );
    mat.rotate( rotate, 0, 0, 1 );
    mat.scale( 1/bufferAspect, 1, 1 );

    mat.translate( x, y, 0 );

    return mat;
  };

protected:
  void addSubControls() {
    mode.setEnumKey( "cover", ofxLoopinTransform2DMode::COVER );
    mode.setEnumKey( "contain", ofxLoopinTransform2DMode::CONTAIN );

    addSubControl( "mode", &mode );
    addSubControl( "x", &x );
    addSubControl( "y", &y );
    addSubControl( "aspect", &aspect );
    addSubControl( "scale", &scale );
    addSubControl( "rotate", &rotate );

  };
};
