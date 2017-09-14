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

class ofxLoopinMeshBase : public ofxLoopinControl {
public:
  ofxLoopinControlNumber aspect;

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

  int makePlaneVertex( float cx, float cy, int x, int y, int w, int h );
  void addTriangle( ofIndexType a, ofIndexType b, ofIndexType c );
  void setModeTriangles();
  void setModePoints();

  int meta_count = 1;
  int meta_cols  = 1;
  int meta_rows  = 1;

protected:
  ofMesh _mesh;

  virtual void addSubControls() {
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
    }
  }

  void setIndices( const Json::Value & val );
  void setVertices( const Json::Value & val );
  void setVertexElements( int vertIndex, const Json::Value &val );
  int vertexKeyToAxis( const string &key );
  void setVertexElement( int index, int axis, float value );
};
