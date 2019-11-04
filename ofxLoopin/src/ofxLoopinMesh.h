#pragma once

#include "ofxLoopinMeshBase.h"
#include "./control/Map.hpp"

#include "mesh/arc.h"
#include "mesh/cube.h"
#include "mesh/plane.h"
#include "mesh/scatter.h"
#include "mesh/sphere.h"



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

class ofxLoopinMesh: public ofxLoopinMeshBase {
public:
  ofxLoopin::mesh::plane plane;
  ofxLoopin::mesh::scatter scatter;
  ofxLoopin::mesh::cube cube;
  ofxLoopin::mesh::arc arc;
  ofxLoopin::mesh::sphere sphere;



  ofxLoopinMesh() {
    // std::cerr << "init mesh" << endl;
    plane.mesh = this;
    plane.generate();
  };
protected:
  void addSubControls() {
    ofxLoopinMeshBase::addSubControls();

    plane.mesh = this;
    addSubControl("plane", &plane );

    scatter.mesh = this;
    addSubControl("scatter", &scatter );

    cube.mesh = this;
    addSubControl("cube", &cube );

    arc.mesh = this;
    addSubControl("arc", &arc );

    sphere.mesh = this;
    addSubControl("sphere", &sphere );
  };
};

class ofxLoopinMeshes : public ofxLoopin::control::Map<ofxLoopinMesh> {

};

class ofxLoopinHasMeshes {
public:
  ofxLoopinMeshes meshes;
  ofxLoopin::control::Map<ofxLoopinMesh> * __getMap() { return &meshes; }
};
