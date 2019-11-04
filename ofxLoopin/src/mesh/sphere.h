#include "./MeshGenerator.hpp"

#include "../control/Number.h"
#include "../control/Bool.h"


namespace ofxLoopin { namespace mesh {
class sphere: public ofxLoopin::MeshGenerator {
public:
  ofxLoopin::control::Int   count = 1;
  ofxLoopin::control::Number radius = 1;
  ofxLoopin::control::Number rotate = 0;
  ofxLoopin::control::Int   cols = 16;
  ofxLoopin::control::Int   rows = 32;
  ofxLoopin::control::Bool  split = ofxLoopin::control::Bool( false );

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
