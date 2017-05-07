#include "circle.h"

void ofxLoopin::mesh::circle::generate() {
  mesh->erase();
  mesh->setModeTriangles();

  generateCircle();
}

void ofxLoopin::mesh::circle::generateCircle( ) {
  int cols = ofxLoopin::mesh::circle::cols.getValueInt();
  int rows = ofxLoopin::mesh::circle::rows.getValueInt();
  bool split =  ofxLoopin::mesh::circle::split.getValue();

  cerr << "generateCircle " << cols << " " << rows << endl;

  // vector<int> lastColA;
  //
  //
  //

  vector<int> firstIndexA;
  firstIndexA.resize( rows );

  vector<int> firstIndexB;
  firstIndexB.resize( rows );

  // vector<int> lastIndexB;
  // firstIndexB.resize( rows+1 );

  int lastIndexA, lastIndexD, lastIndexC;

  for ( int row = 0; row < rows; row ++ ) {

    for ( int col = 0; col < cols; col ++ ) {
      int indexA, indexB, indexC, indexD;

      //
      // Vertex A
      //
      if ( split || (!col && !row) ) {
        cerr << "A" << endl;
        indexA = generateCircleVertex( col, row );
      } else if ( !row ) {
        // Centre of circle
        indexA = firstIndexA[row];
      } else {
        indexA = lastIndexD;
      }

      if ( !col ) {
        firstIndexA[row] = indexA;
      }

      lastIndexA = indexA;

      //
      // Vertex B
      //
      if ( split || !col ) {
        cerr << "B" << endl;
        indexB = generateCircleVertex( col, row+1 );
      } else {
        indexB = lastIndexC;
      }
      if ( !col ) {
        firstIndexB[row] = indexB;
      }

      //
      //  Vertex C
      //
      if ( split || col < cols - 1 ) {
        indexC = generateCircleVertex( col+1, row+1 );
      } else {
        indexC = firstIndexB[row];
      }

      lastIndexC = indexC;

      //
      // Vertex D
      //

      if ( split || col < cols - 1 ) {
        indexD = generateCircleVertex( col+1, row );
      } else if ( col == cols -1 ) {
        indexD = firstIndexA[row];
      } else {
        indexD = lastIndexA;
      }

      addTriangle( indexA, indexB, indexC );

      if ( row || split )
        addTriangle( indexC, indexD, indexA );
    }
  }

  // exit( 0 );
}

int ofxLoopin::mesh::circle::generateCircleVertex( int col, int row ) {
  float radius = ofxLoopin::mesh::circle::radius;
  int cols = ofxLoopin::mesh::circle::cols.getValueInt();
  int rows = ofxLoopin::mesh::circle::rows.getValueInt();

  float u = (float) col / (float) cols;
  float v = (float) row / (float) rows;

  float a = u * 2.0 * M_PI;
  float r = v * radius;

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
