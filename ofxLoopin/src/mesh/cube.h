#include "./MeshGenerator.hpp"

#include "../control/Number.hpp"
#include "../control/Bool.hpp"


namespace ofxLoopin { namespace mesh {
class cube : public ofxLoopin::MeshGenerator {
public:
  ofxLoopin::control::Int   count = 1;


  void addSubControls() {
    addSubControl( "count", &count );
  };
  void generate();

protected:
  void makeCube();
  void makeCubeFace( int cubeIndex, int faceIndex );
  int makeCubeVertex( int cubeIndex, int faceIndex, ofVec3f normal, ofVec2f uv );
};
} }
