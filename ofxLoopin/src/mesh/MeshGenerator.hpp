#pragma once

#include "ofxLoopinControl.h"
#include "ofxLoopinMeshBase.h"


#include "ofMesh.h"
#include "util/ofxLoopinJSON.hpp"

namespace ofxLoopin {
  class MeshGenerator : public ofxLoopinControl {
  public:
    ofxLoopinMeshBase * mesh = nullptr;

  protected:

    void patchLocalAfter( const ofJson & value ) {
      if ( ofxLoopinJSONToBool( value ) ) {
        generate();
      }
    };

    virtual void generate() {};

    void erase();

    int addVertex(
      float x, float y, float z,
      float u, float v,
      float r, float g, float b, float a,
      float nx, float ny, float nz
    ) {
      assert( mesh );
      return mesh->addVertex( x, y, z, u, v, r, g, b, a, nx, ny, nz );
    };

    void addTriangle( ofIndexType a, ofIndexType b, ofIndexType c ) {
      assert( mesh );
      mesh->addTriangle( a, b, c );
    }
  };
}
