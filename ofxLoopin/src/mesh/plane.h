#include "../MeshGenerator.h"

#include "../ofxLoopinControlNumber.h"
#include "../ofxLoopinControlBool.h"


namespace ofxLoopin { namespace mesh {
class plane : public ofxLoopin::MeshGenerator {
public:
  ofxLoopinControlInt   count = 1;
  ofxLoopinControlInt   cols = 1;
  ofxLoopinControlInt   rows = 1;
  ofxLoopinControlBool  split = ofxLoopinControlBool( false );
  ofxLoopinControlBool  weave = ofxLoopinControlBool( false );

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
