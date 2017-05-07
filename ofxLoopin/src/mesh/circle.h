#include "../MeshGenerator.h"

#include "../ofxLoopinControlNumber.h"
#include "../ofxLoopinControlBool.h"


namespace ofxLoopin { namespace mesh {
class circle: public ofxLoopin::MeshGenerator {
public:
  ofxLoopinControlNumber radius = 1;
  ofxLoopinControlInt   cols = 4;
  ofxLoopinControlInt   rows = 2;
  ofxLoopinControlBool  split = ofxLoopinControlBool( false );

  void addSubControls() {
    addSubControl( "cols", &cols );
    addSubControl( "rows", &rows );
    addSubControl( "split", &split );
  }

  void generate();
  void generateCircle();
  int generateCircleVertex( int row, int col );
};
} }
