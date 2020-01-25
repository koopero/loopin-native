#pragma once

#include "./control/Control.hpp"
#include "./control/Number.hpp"

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

namespace ofxLoopin { namespace render {

enum Transform2DMode {
  COVER, CONTAIN
 };

class Transform2D : public ofxLoopin::control::Control {
public:
  ofxLoopin::control::Number x;
  ofxLoopin::control::Number y;
  ofxLoopin::control::Number aspect = ofxLoopin::control::Number(1);
  ofxLoopin::control::Number scale = ofxLoopin::control::Number(1);
  ofxLoopin::control::Number rotate;
  ofxLoopin::control::Enum<Transform2DMode,Transform2DMode::COVER> mode;

  ofMatrix4x4 makeMatrix ( float layerAspect, float bufferAspect ) const  {
    // std::cerr << "transform2D::layerAspect " << layerAspect << endl;
    // std::cerr << "transform2D::bufferAspect " << bufferAspect << endl;

    ofMatrix4x4 mat;
    // float ourAspect = aspect;
    float scale = Transform2D::scale;

    switch ( mode.getEnumValue() ) {
      case Transform2DMode::COVER:
        if ( fabs(layerAspect) < fabs(bufferAspect) ) {
          scale *= bufferAspect / layerAspect;
        }
      break;

      case Transform2DMode::CONTAIN:
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
    mode.enumAddOption( "cover", Transform2DMode::COVER );
    mode.enumAddOption( "contain", Transform2DMode::CONTAIN );

    addSubControl( "mode", &mode );
    addSubControl( "x", &x );
    addSubControl( "y", &y );
    addSubControl( "aspect", &aspect );
    addSubControl( "scale", &scale );
    addSubControl( "rotate", &rotate );

  };
};
}};