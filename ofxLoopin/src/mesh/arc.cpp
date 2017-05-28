#include "arc.h"

void ofxLoopin::mesh::arc::generate() {
  mesh->erase();
  mesh->setModeTriangles();

  generateArc();
}

void ofxLoopin::mesh::arc::generateArc( ) {
  int cols = ofxLoopin::mesh::arc::cols.getValueInt();
  int rows = ofxLoopin::mesh::arc::rows.getValueInt();
  bool split =  ofxLoopin::mesh::arc::split.getValue();

  // cerr << endl << "generateArc " << cols << " " << rows << endl;

  vector<int> lastIndexC;
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
        indexA = generateArcVertex( col + offset, row );
      } else if ( !col ) {
        indexA = firstIndexB;
      } else {
        indexA = lastIndexD;
      }


      //
      // Vertex B
      //
      if ( split || !col ) {
        indexB = generateArcVertex( col, row+1 );
      } else {
        indexB = lastIndexC[col-1];
      }

      if ( !col ) {
        firstIndexB = indexB;
      }

      //
      //  Vertex C
      //
      indexC = generateArcVertex( col+1, row+1 );


      //
      // Vertex D
      //

      if ( split || !row ) {
        indexD = generateArcVertex( col+1, row );
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

int ofxLoopin::mesh::arc::generateArcVertex( int col, int row ) {
  float radius = ofxLoopin::mesh::arc::radius;
  float inner = ofxLoopin::mesh::arc::inner;

  float rotate = ofxLoopin::mesh::arc::rotate;
  float span = ofxLoopin::mesh::arc::span;

  int cols = ofxLoopin::mesh::arc::cols.getValueInt();
  int rows = ofxLoopin::mesh::arc::rows.getValueInt();

  float u = (float) col / (float) cols;
  float v = (float) row / (float) rows;

  float a = ( u * span/360.0 + rotate / 360.0 ) * 2.0 * M_PI;
  float r = v * (radius-inner) + inner;

  float s = sin(a);
  float c = -cos(a);

  float x = s * r;
  float y = c * r;

  return addVertex(
    x, y, 0, // x,y,z
    u, v,    // u,v
    0, 0,    // r,g
    0, // b
    0, // a
    s, c,       // nx, ny
    1 // nz
  );
};
