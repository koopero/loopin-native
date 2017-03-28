#pragma once

#include "ofxLoopinControl.h"
#include "ofxLoopinControlEnum.h"
#include "ofxLoopinControlNumber.h"

#include "ofxLoopinMap.h"

#include "ofMesh.h"

/** loopin/root/mesh:
  map: mesh
*/

/** loopin/type/mesh/sub:
plane:
  type: trigger
  args:
    rows:
      type: int
      min: 1
      max: 256
      default: 1
    cols:
      type: int
      min: 1
      max: 256
      default: 1
    split/type: bool
    weave/type: bool

cube:
  type: trigger
  args:
    count:
      type: int
      min: 1
      max: 256
      default: 1

scatter:
  type: trigger
  args:
    count:
      type: int
      min: 1
      max: 256
      default: 1
    seed:
      type: int
      min: -1
      default: -1
*/

class ofxLoopinMesh : public ofxLoopinControl {
public:
  ofxLoopinControlNumber aspect;

  ofxLoopinMesh() {
    makePlane();
  };

  void draw() {
    _mesh.setMode( mode.getEnumValue() );
    _mesh.draw();
  };

  ofxLoopinControlEnum<ofPrimitiveMode,OF_PRIMITIVE_TRIANGLES> mode;

  void erase();

  int addVertex(
    float x, float y, float z,
    float u, float v,
    float r, float g, float b, float a,
    float nx, float ny, float nz
  );

  void makePlane( const Json::Value & val );
  void makePlane( int wInd = 1, int hInd = 1, bool split = true, bool weave = true );

  void makeScatter( const Json::Value & val );
  void makeScatter( int num = 64, int seed = -1 );

  void makeCube( const Json::Value & val );
  void makeCube( int count = 1 );
  void makeCubeFace( int cubeIndex, int faceIndex );
  int makeCubeVertex( int cubeIndex, int faceIndex, ofVec3f normal, ofVec2f uv );


  int makePlaneVertex( float cx, float cy, int x, int y, int w, int h );
  void makePlaneTri( ofIndexType a, ofIndexType b, ofIndexType c );


protected:
  ofMesh _mesh;

  int _planeCols = 4;
  int _planeRows = 3;
  bool _planeSplit = false;
  bool _planeWeave = false;


  void addSubControls() {
    addSubControl("aspect", &aspect );

    mode.setEnumKey("triangles", OF_PRIMITIVE_TRIANGLES );
    mode.setEnumKey("points", OF_PRIMITIVE_POINTS );

    addSubControl("mode", &mode );
  };

  void patchLocal( const Json::Value & val ) {
    if ( val.isObject() ) {
      if ( val.isMember("vertex") )
        setVertices( val["vertex"] );

      if ( val.isMember("index") )
        setIndices( val["index"] );

      if ( val.isMember("plane") ) {
        makePlane( val["plane"] );
      }

      if ( val.isMember("cube") ) {
        makeCube( val["cube"] );
      }

      if ( val.isMember("scatter") )
        makeScatter( val["scatter"] );
    }
  }

  void setIndices( const Json::Value & val );
  void setVertices( const Json::Value & val );
  void setVertexElements( int vertIndex, const Json::Value &val );
  int vertexKeyToAxis( const string &key );
  void setVertexElement( int index, int axis, float value );
};

class ofxLoopinMeshes : public ofxLoopinMap<ofxLoopinMesh> {

};

class ofxLoopinHasMeshes {
public:
  ofxLoopinMeshes meshes;
  ofxLoopinMap<ofxLoopinMesh> * __getMap() { return &meshes; }
};
