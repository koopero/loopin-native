#pragma once

#include "./Vector.hpp"

namespace ofxLoopin { namespace control {
class Colour : public Vector<4> {
public:
  void setColor( const ofFloatColor & color ) {
    setAxis( 0, color.r );
    setAxis( 1, color.g );
    setAxis( 2, color.b );
    setAxis( 3, color.a );
  }

  ofFloatColor asFloatColor() {
    return ofFloatColor(
      getAxis( 0 ),
      getAxis( 1 ),
      getAxis( 2 ),
      getAxis( 3 )
    );
  }
};
}} // namespace