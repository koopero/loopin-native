#include "./MeshGenerator.hpp"

#include "../control/Number.h"
#include "../control/Bool.h"


namespace ofxLoopin { namespace mesh {
class scatter : public ofxLoopin::MeshGenerator {
public:
  ofxLoopin::control::Int   seed = -1;
  ofxLoopin::control::Int   count = 256;

  void addSubControls() {
    addSubControl( "seed", &seed );
    addSubControl( "count", &count );
  }

  void generate();
  void makeScatter( int num, int seed );
};
} }
