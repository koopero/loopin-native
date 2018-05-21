#include "sphere.h"

void ofxLoopin::mesh::sphere::generate() {
  mesh->erase();
  mesh->setModeTriangles();

  mesh->meta_cols = cols;
  mesh->meta_rows = rows;
  mesh->meta_count = count;

  for ( int index = 0; index < count; index ++ )
    generateSphere( index );
}

void ofxLoopin::mesh::sphere::generateSphere( int index ) {
  int cols = ofxLoopin::mesh::sphere::cols.getValueInt();
  int rows = ofxLoopin::mesh::sphere::rows.getValueInt();
  bool split =  ofxLoopin::mesh::sphere::split.getValue();

  std::vector<int> lastIndexC;
  lastIndexC.resize( cols );

  int firstIndexB, lastIndexA, lastIndexD;

  for ( int row = 0; row < rows; row ++ ) {

    for ( int col = 0; col < cols; col ++ ) {
      int indexA, indexB, indexC, indexD;

      //
      // Vertex A
      //
      if ( split || (!col && !row) ) {
        float offset = 0;
        indexA = generateSphereVertex( index, col + offset, row );
      } else if ( !col ) {
        indexA = firstIndexB;
      } else {
        indexA = lastIndexD;
      }


      //
      // Vertex B
      //
      if ( split || !col ) {
        indexB = generateSphereVertex( index, col, row+1 );
      } else {
        indexB = lastIndexC[col-1];
      }

      if ( !col ) {
        firstIndexB = indexB;
      }

      //
      //  Vertex C
      //
      indexC = generateSphereVertex( index, col+1, row+1 );


      //
      // Vertex D
      //

      if ( split || !row ) {
        indexD = generateSphereVertex( index, col+1, row );
      } else {
        indexD = lastIndexC[col];
      }

      addTriangle( indexA, indexB, indexC );
      addTriangle( indexC, indexD, indexA );

      lastIndexA = indexA;
      lastIndexD = indexD;
      lastIndexC[col] = indexC;

    }
  }

  // exit( 0 );
}

int ofxLoopin::mesh::sphere::generateSphereVertex( int index, int col, int row ) {
  int cols = ofxLoopin::mesh::sphere::cols.getValueInt();
  int rows = ofxLoopin::mesh::sphere::rows.getValueInt();

  float u = (float) col / (float) cols;
  float v = (float) row / (float) rows;

  float rz = v * 180 - 90;
  float ry = u * 360 + rotate;

  ofVec3f norm = ofVec3f( 1.0, 0, 0 );
  norm = norm.rotate( rz, ofVec3f( 0,0,1 ) );
  norm = norm.rotate( ry, ofVec3f( 0,1,0 ) );

  ofVec3f pos = norm * radius;

  return addVertex(
    pos.x, pos.y, pos.z, // x,y,z
    u, v,    // u,v
    0, 0,   // r,g
    count > 1 ? (float) index / (float) (count-1) : 0.5,  // b
    0,       // a
    norm.x, norm.y, norm.z     // nx, ny, nz
  );
};
