#include "plane.h"

void ofxLoopin::mesh::plane::generate() {
  mesh->erase();
  mesh->setModeTriangles();

  mesh->meta_cols = cols;
  mesh->meta_rows = rows;
  mesh->meta_count = count;

  for ( int index = 0; index < count; index ++ )
    makePlane( index );

}

void ofxLoopin::mesh::plane::makePlane( int index ) {
  int wInd = cols.getValueInt();
  int hInd = rows.getValueInt();
  bool split = ofxLoopin::mesh::plane::split;
  bool weave = ofxLoopin::mesh::plane::weave;

  int vertIndex = 0;
  int rowIndex;
  int cellIndex;

  int lastBL;


  std::vector<int> lastBR;
  lastBR.resize( wInd );
  //
  //
  //

  for ( int yInd = 0; yInd < hInd; yInd ++ ) {
    rowIndex = vertIndex;
    for ( int xInd = 0; xInd < wInd; xInd ++ ) {
      cellIndex = vertIndex;

      int tl, tr, bl, br, centre;

      if ( split || (!xInd && !yInd) ) {
        tl = makePlaneVertex( index, 0, 0, xInd, yInd, wInd, hInd );
      } else if ( xInd ){
        tl = tr;
      } else {
        tl = lastBL;
      }

      if ( split || !yInd ) {
        tr = makePlaneVertex( index, 1, 0, xInd, yInd, wInd, hInd );
      } else {
        tr = lastBR[xInd];
      }

      br = makePlaneVertex( index, 1, 1, xInd, yInd, wInd, hInd );

      if ( split || !xInd ) {
        bl = makePlaneVertex( index, 0, 1, xInd, yInd, wInd, hInd );
      } else {
        bl = lastBR[xInd-1];
      }

      if ( !xInd )
        lastBL = bl;

      if ( weave ) {
        centre = makePlaneVertex( index, 0.5, 0.5, xInd, yInd, wInd, hInd );
        addTriangle( tl, tr, centre );
        addTriangle( tr, br, centre );
        addTriangle( br, bl, centre );
        addTriangle( bl, tl, centre );
      } else {
        centre = -1;
        addTriangle( tl, tr, br );
        addTriangle( br, bl, tl );
      }

      vertIndex = fmax( bl, centre );
      lastBR[xInd] = br;

    }
  }

  // exit( 0 );
}

int ofxLoopin::mesh::plane::makePlaneVertex( int index, float cx, float cy, int x, int y, int w, int h ) {

  float ul = ( x + 0 ) / (float) w ;
  float ur = ( x + 1 ) / (float) w ;
  float vt = ( y + 0 ) / (float) h ;
  float vb = ( y + 1 ) / (float) h ;

  float xl = ul * 2.0 - 1.0;
  float xr = ur * 2.0 - 1.0;
  float yt = vt * 2.0 - 1.0;
  float yb = vb * 2.0 - 1.0;

  float xf = xl + ( xr - xl ) * cx;
  float yf = yt + ( yb - yt ) * cy;

  float uf = ul + ( ur - ul ) * cx;
  float vf = vt + ( vb - vt ) * cy;

  return addVertex(
    xf, yf, 0, // x,y,z
    uf, vf,    // u,v
    cx, cy,    // r,g
    (float) index / (float) (count),  // b
    vt + ( vb - vt ) * 0.5, // a
    w, h,       // nx, ny
    1 // nz
  );
};
