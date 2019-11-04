#include "./MeshGenerator.hpp"

#include "../control/Number.hpp"
#include "../control/Bool.hpp"


namespace ofxLoopin { namespace mesh {
class arc: public ofxLoopin::mesh::MeshGenerator {
public:
  ofxLoopin::control::Int   count = 1;
  ofxLoopin::control::Number radius = 1;
  ofxLoopin::control::Number inner = 0.0;
  ofxLoopin::control::Number rotate = 0;
  ofxLoopin::control::Number span = 360;
  ofxLoopin::control::Int   cols = 64;
  ofxLoopin::control::Int   rows = 8;
  ofxLoopin::control::Bool  split = ofxLoopin::control::Bool( false );

  void addSubControls() {
    addSubControl( "count", &count );
    addSubControl( "cols", &cols );
    addSubControl( "rows", &rows );
    addSubControl( "rotate", &rotate );
    addSubControl( "radius", &radius );
    addSubControl( "span", &span );
    addSubControl( "inner", &inner );
    addSubControl( "split", &split );
  }

  void generate();
  void generateArc( int index );
  int generateArcVertex( int index, int row, int col, float qx, float qy );
};
} }
