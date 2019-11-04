#include "./MeshGenerator.hpp"

#include "../control/Number.h"
#include "../control/Bool.h"


namespace ofxLoopin { namespace mesh {
class plane : public ofxLoopin::MeshGenerator {
public:
  ofxLoopin::control::Int   count = 1;
  ofxLoopin::control::Int   cols = 1;
  ofxLoopin::control::Int   rows = 1;
  ofxLoopin::control::Bool  split = ofxLoopin::control::Bool( false );
  ofxLoopin::control::Bool  weave = ofxLoopin::control::Bool( false );

  void addSubControls() {
    addSubControl( "count", &count );
    addSubControl( "cols", &cols );
    addSubControl( "rows", &rows );
    addSubControl( "split", &split );
    addSubControl( "weave", &weave );
  }
  void generate();
  void makePlane( int index );
  int makePlaneVertex( int index, float cx, float cy, int x, int y, int w, int h );
  void makePlaneTri( ofIndexType a, ofIndexType b, ofIndexType c );

};
} }
