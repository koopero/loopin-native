#include "scatter.h"

/**
## Scatter
*/
void ofxLoopin::mesh::scatter::generate() {
  assert( mesh );

  makeScatter( count.getValueInt(), seed.getValueInt() );
}

void ofxLoopin::mesh::scatter::makeScatter( int num, int seed ) {
  mesh->erase();
  mesh->setModePoints();

  if ( seed >= 0 )
    ofSeedRandom( seed );
  else
    ofSeedRandom();

  float density = 1.0 / ( float ) num;

  for ( int i = 0; i < num; i ++ ) {

    float u = (float) i / (float) num;
    float v = (float) i / ( (float) num - 1.0 );

    ofVec3f norm( ofRandom( -1, 1 ), ofRandom( -1, 1 ), ofRandom( -1, 1 ) );
    norm /= norm.length();

    addVertex(
        // x, y, z
        ofRandom( -1, 1 ), ofRandom( -1, 1 ), ofRandom( -1, 1 ),

        // u, v
        u, v,

        // r g b a
        ofRandom( 0, 1 ), ofRandom( 0, 1 ), ofRandom( 0, 1 ), density,

        // nx, ny, nz
        norm.x, norm.y, norm.z
    );
  }

}
