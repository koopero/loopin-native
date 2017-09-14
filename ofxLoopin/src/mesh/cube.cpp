#include "cube.h"

void ofxLoopin::mesh::cube::generate() {
  mesh->meta_cols = 1;
  mesh->meta_rows = 1;
  mesh->meta_count = count;

  makeCube();
}

void ofxLoopin::mesh::cube::makeCube() {
  mesh->erase();
  mesh->setModeTriangles();

  for ( int cubeIndex = 0; cubeIndex < count; cubeIndex ++ ) {
    for ( int faceIndex = 0; faceIndex < 6; faceIndex ++ ) {
      makeCubeFace( cubeIndex, faceIndex );
    }
  }
}

void ofxLoopin::mesh::cube::makeCubeFace( int cubeIndex, int faceIndex ) {
  ofVec3f normal;

  switch( faceIndex ) {
    case 0: normal.z =  1; break; // front
    case 1: normal.z = -1; break; // back

    case 2: normal.x = -1; break; // left
    case 3: normal.x =  1; break; // right

    case 4: normal.y =  1; break; // top
    case 5: normal.y = -1; break; // bottom
  }
  int tl = makeCubeVertex( cubeIndex, faceIndex, normal, ofVec2f( 0, 0 ) );
  int tr = makeCubeVertex( cubeIndex, faceIndex, normal, ofVec2f( 1, 0 ) );
  int br = makeCubeVertex( cubeIndex, faceIndex, normal, ofVec2f( 1, 1 ) );
  int bl = makeCubeVertex( cubeIndex, faceIndex, normal, ofVec2f( 0, 1 ) );

  addTriangle( tl, tr, br );
  addTriangle( br, bl, tl );
}

int ofxLoopin::mesh::cube::makeCubeVertex( int cubeIndex, int faceIndex, ofVec3f normal, ofVec2f uv ) {

  ofVec3f pos = normal;
  ofVec3f plane = uv * 2.0 - ofVec2f( 1, 1 );

  switch( faceIndex ) {
    case 0: pos.x =  plane.x; pos.y =  plane.y; break; // front
    case 1: pos.x = -plane.x; pos.y =  plane.y; break; // back

    case 2: pos.z =  plane.x; pos.y =  plane.y; break; // left
    case 3: pos.z = -plane.x; pos.y =  plane.y; break; // right

    case 4: pos.x =  plane.x; pos.z = -plane.y; break; // top
    case 5: pos.x =  plane.x; pos.z =  plane.y; break; // bottom
  }

  return addVertex(
    pos.x, pos.y, pos.z, // x,y,z
    uv.x, uv.y,    // u,v
    cubeIndex, faceIndex,    // r,g
    count > 1 ? (float) cubeIndex / (float) (count-1) : 0.5, // b
    1, // a
    normal.x, normal.y, normal.z
  );

}
