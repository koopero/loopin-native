#pragma once

#include "./Vector.hpp"

namespace ofxLoopin { namespace control {
class Colour : public Vector<4> {
public:
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