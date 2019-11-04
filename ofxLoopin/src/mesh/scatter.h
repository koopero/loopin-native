#include "./MeshGenerator.hpp"

#include "../control/Number.hpp"
#include "../control/Bool.hpp"


namespace ofxLoopin { namespace mesh {
class scatter : public ofxLoopin::mesh::MeshGenerator {
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
