#pragma once

#include "./MeshBase.hpp"
#include "../control/Map.hpp"

#include "./arc.h"
#include "./cube.h"
#include "./plane.h"
#include "./scatter.h"
#include "./sphere.h"

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

namespace ofxLoopin { namespace mesh {
class Mesh: public MeshBase {
public:
  ofxLoopin::mesh::plane plane;
  ofxLoopin::mesh::scatter scatter;
  ofxLoopin::mesh::cube cube;
  ofxLoopin::mesh::arc arc;
  ofxLoopin::mesh::sphere sphere;

  Mesh() {
    // std::cerr << "init mesh" << endl;
    plane.mesh = this;
    plane.generate();
  };
protected:
  void addSubControls() {
    MeshBase::addSubControls();

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

class Meshes : public control::Map<Mesh> {

};

class HasMeshes {
public:
  Meshes meshes;
  control::Map<Mesh> * __getMap() { return &meshes; }
};
}};