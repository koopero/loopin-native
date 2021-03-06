#pragma once

#include "./Vector.hpp"
#include "ofGraphics.h"

namespace ofxLoopin { namespace control {

class Box : public Vector<4> {
public:
  ofRectangle getRectangle() {
    return ofRectangle( getAxis(0), getAxis(1), getAxis(2), getAxis(3) );
  }

  ofRectangle getFittedRectangle( ofRectangle within ) {
    ofRectangle result = getRectangle();

    if ( result.getWidth() <= 0 )
      result.setWidth( within.getWidth() + result.getWidth() );

    if ( result.getHeight() <= 0 )
      result.setHeight( within.getHeight() + result.getHeight() );

    return result;
  }

  float getX() { return getAxis( 0 ); }
  float getY() { return getAxis( 1 ); }
  float getWidth() { return getAxis( 2 ); }
  float getHeight() { return getAxis( 3 ); }


protected:
  int keyToAxis( const string & key ) {
    if ( key == "x" || key == "0" ) return 0;
    if ( key == "y" || key == "1" ) return 1;
    if ( key == "w" || key == "width" || key == "2" ) return 2;
    if ( key == "h" || key == "height" || key == "3" ) return 3;
    return -1;
  }
};
}}
