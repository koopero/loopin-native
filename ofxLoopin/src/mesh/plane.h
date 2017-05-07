#include "../MeshGenerator.h"

#include "../ofxLoopinControlNumber.h"
#include "../ofxLoopinControlBool.h"


namespace ofxLoopin { namespace mesh {
class plane : public ofxLoopin::MeshGenerator {
public:
  ofxLoopinControlInt   cols = 1;
  ofxLoopinControlInt   rows = 1;
  ofxLoopinControlBool  split = ofxLoopinControlBool( false );
  ofxLoopinControlBool  weave = ofxLoopinControlBool( false );

  void addSubControls() {
    addSubControl( "cols", &cols );
    addSubControl( "rows", &rows );
    addSubControl( "split", &split );
    addSubControl( "weave", &weave );
  }
  void generate();
  void makePlane( int wInd, int hInd, bool split, bool weave );
  int makePlaneVertex( float cx, float cy, int x, int y, int w, int h );
  void makePlaneTri( ofIndexType a, ofIndexType b, ofIndexType c );

};
} }
