#include "../MeshGenerator.h"

#include "../ofxLoopinControlNumber.h"
#include "../ofxLoopinControlBool.h"


namespace ofxLoopin { namespace mesh {
class scatter : public ofxLoopin::MeshGenerator {
public:
  ofxLoopinControlInt   seed = -1;
  ofxLoopinControlInt   count = 256;

  void addSubControls() {
    addSubControl( "seed", &seed );
    addSubControl( "count", &count );
  }

  void generate();
  void makeScatter( int num, int seed );
};
} }
