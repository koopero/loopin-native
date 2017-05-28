#include "../MeshGenerator.h"

#include "../ofxLoopinControlNumber.h"
#include "../ofxLoopinControlBool.h"


namespace ofxLoopin { namespace mesh {
class cube : public ofxLoopin::MeshGenerator {
public:
  void addSubControls() {
    
  };
  void generate();

protected:
  void makeCube( int count );
  void makeCubeFace( int cubeIndex, int faceIndex );
  int makeCubeVertex( int cubeIndex, int faceIndex, ofVec3f normal, ofVec2f uv );
};
} }
