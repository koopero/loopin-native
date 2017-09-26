#include "../MeshGenerator.h"

#include "../ofxLoopinControlNumber.h"
#include "../ofxLoopinControlBool.h"


namespace ofxLoopin { namespace mesh {
class arc: public ofxLoopin::MeshGenerator {
public:
  ofxLoopinControlInt   count = 1;
  ofxLoopinControlNumber radius = 1;
  ofxLoopinControlNumber inner = 0.0;
  ofxLoopinControlNumber rotate = 0;
  ofxLoopinControlNumber span = 360;
  ofxLoopinControlInt   cols = 64;
  ofxLoopinControlInt   rows = 8;
  ofxLoopinControlBool  split = ofxLoopinControlBool( false );

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
