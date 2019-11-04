#pragma once

#include "./control/Control.hpp"
#include "./control/Enum.hpp"
#include "ofxLoopin::control::Number.h"
#include "ofxLoopinMap.h"
#include "util/ofxLoopinJSON.hpp"
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

class ofxLoopinMeshBase : public ofxLoopin::control::Control {
public:
  ofxLoopin::control::Number aspect;

  void draw() {
    _mesh.setMode( mode.getEnumValue() );
    _mesh.draw();
  };

  ofxLoopin::control::Enum<ofPrimitiveMode,OF_PRIMITIVE_TRIANGLES> mode;

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

  void patchLocal( const ofJson & val ) {
    if ( val.is_object() ) {
      if ( val.count("vertex") )
        setVertices( val["vertex"] );

      if ( val.count("index") )
        setIndices( val["index"] );
    }
  }

  void setIndices( const ofJson & val );
  void setIndex( int index, const ofJson & val );
  void setVertices( const ofJson & val );
  void setVertexElements( int vertIndex, const ofJson & val );
  int vertexKeyToAxis( const string &key );
  void setVertexElement( int index, int axis, float value );
};
