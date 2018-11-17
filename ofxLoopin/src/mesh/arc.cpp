#include "arc.h"

void ofxLoopin::mesh::arc::generate() {
  mesh->erase();
  mesh->setModeTriangles();

  mesh->meta_cols = cols;
  mesh->meta_rows = rows;
  mesh->meta_count = count;

  for ( int index = 0; index < count; index ++ )
    generateArc( index );
}

void ofxLoopin::mesh::arc::generateArc( int index ) {
  int cols = ofxLoopin::mesh::arc::cols.getValueInt();
  int rows = ofxLoopin::mesh::arc::rows.getValueInt();
  bool split =  ofxLoopin::mesh::arc::split.getValue();

  // std::cerr << endl << "generateArc " << cols << " " << rows << endl;

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
        indexA = generateArcVertex( index, col, row, 0, 0 );
      } else if ( !col ) {
        indexA = firstIndexB;
      } else {
        indexA = lastIndexD;
      }


      //
      // Vertex B
      //
      if ( split || !col ) {
        indexB = generateArcVertex( index, col, row+1, 0, 1 );
      } else {
        indexB = lastIndexC[col-1];
      }

      if ( !col ) {
        firstIndexB = indexB;
      }

      //
      //  Vertex C
      //
      indexC = generateArcVertex( index, col+1, row+1, 1, 1 );


      //
      // Vertex D
      //

      if ( split || !row ) {
        indexD = generateArcVertex( index, col+1, row, 1, 0 );
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

int ofxLoopin::mesh::arc::generateArcVertex( int index, int col, int row, float qx, float qy ) {
  float radius = ofxLoopin::mesh::arc::radius;
  float inner = ofxLoopin::mesh::arc::inner;

  float rotate = ofxLoopin::mesh::arc::rotate;
  float span = ofxLoopin::mesh::arc::span;

  int cols = ofxLoopin::mesh::arc::cols.getValueInt();
  int rows = ofxLoopin::mesh::arc::rows.getValueInt();

  float u = (float) col / (float) cols;
  float v = (float) row / (float) rows;

  float a = ( u * span/360.0 + rotate / 360.0 ) * 2.0 * 3.141592654;
  float r = v * (radius-inner) + inner;

  float s = sin(a);
  float c = -cos(a);

  float x = s * r;
  float y = c * r;

  return addVertex(
    x, y, 0, // x,y,z
    u, v,    // u,v
    qx, qy,    // r,g
    (float) index / (float) count, // b
    1.0, // a
    s, c,       // nx, ny
    1 // nz
  );
};
