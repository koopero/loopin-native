#include "../MeshGenerator.h"

#include "../ofxLoopinControlNumber.h"
#include "../ofxLoopinControlBool.h"


namespace ofxLoopin { namespace mesh {
class arc: public ofxLoopin::MeshGenerator {
public:
  ofxLoopinControlNumber radius = 1;
  ofxLoopinControlNumber inner = 0.5;
  ofxLoopinControlNumber rotate = 0;
  ofxLoopinControlNumber span = 360;
  ofxLoopinControlInt   cols = 4;
  ofxLoopinControlInt   rows = 2;
  ofxLoopinControlBool  split = ofxLoopinControlBool( false );

  void addSubControls() {
    addSubControl( "cols", &cols );
    addSubControl( "rows", &rows );
    addSubControl( "rotate", &rotate );
    addSubControl( "radius", &radius );
    addSubControl( "span", &span );
    addSubControl( "inner", &inner );
    addSubControl( "split", &split );
  }

  void generate();
  void generateArc();
  int generateArcVertex( int row, int col );
};
} }
