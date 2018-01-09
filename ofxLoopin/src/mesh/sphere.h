#include "./MeshGenerator.hpp"

#include "../ofxLoopinControlNumber.h"
#include "../ofxLoopinControlBool.h"


namespace ofxLoopin { namespace mesh {
class sphere: public ofxLoopin::MeshGenerator {
public:
  ofxLoopinControlInt   count = 1;
  ofxLoopinControlNumber radius = 1;
  ofxLoopinControlNumber rotate = 0;
  ofxLoopinControlInt   cols = 16;
  ofxLoopinControlInt   rows = 32;
  ofxLoopinControlBool  split = ofxLoopinControlBool( false );

  void addSubControls() {
    addSubControl( "count",  &count );
    addSubControl( "cols",   &cols );
    addSubControl( "rows",   &rows );
    addSubControl( "radius", &radius );
    addSubControl( "split",  &split );
  }

  void generate();
  void generateSphere( int index );
  int generateSphereVertex( int index, int row, int col );
};
} }
