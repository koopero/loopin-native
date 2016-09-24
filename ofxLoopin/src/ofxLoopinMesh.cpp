#include "ofxLoopinMesh.h"

void ofxLoopinMesh::erase() {
  _mesh.getIndices().resize(0);
  _mesh.getVertices().resize(0);
  _mesh.getTexCoords().resize(0);
  _mesh.getColors().resize(0);
  _mesh.getNormals().resize(0);
};

void ofxLoopinMesh::makePlane( const Json::Value & val ) {
  int rows = 1;
  int cols = 1;

  bool split = false;
  bool weave = false;

  if ( val.isObject() ) {
    if ( val.isMember("rows") && val["rows"].isInt() ) rows = val["rows"].asInt();
    if ( val.isMember("cols") && val["cols"].isInt() ) cols = val["cols"].asInt();
    if ( val.isMember("split") && val["split"].isBool() )
      split = val["split"].asBool();
    if ( val.isMember("weave") && val["weave"].isBool() )
      weave = val["weave"].asBool();
  }

  makePlane( cols, rows, split, weave );
}

void ofxLoopinMesh::makePlane( int wInd, int hInd, bool split, bool weave ) {
  erase();
  mode.setKey("triangles");

  int vertIndex = 0;
  int rowIndex;
  int cellIndex;

  int lastBL;


  vector<int> lastBR;
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
        tl = makePlaneVertex( 0, 0, xInd, yInd, wInd, hInd );
      } else if ( xInd ){
        tl = tr;
      } else {
        tl = lastBL;
      }

      if ( split || !yInd ) {
        tr = makePlaneVertex( 1, 0, xInd, yInd, wInd, hInd );
      } else {
        tr = lastBR[xInd];
      }

      br = makePlaneVertex( 1, 1, xInd, yInd, wInd, hInd );

      if ( split || !xInd ) {
        bl = makePlaneVertex( 0, 1, xInd, yInd, wInd, hInd );
      } else {
        bl = lastBR[xInd-1];
      }

      if ( !xInd )
        lastBL = bl;

      if ( weave ) {
        centre = makePlaneVertex( 0.5, 0.5, xInd, yInd, wInd, hInd );
        makePlaneTri( tl, tr, centre );
        makePlaneTri( tr, br, centre );
        makePlaneTri( br, bl, centre );
        makePlaneTri( bl, tl, centre );
      } else {
        centre = -1;
        makePlaneTri( tl, tr, br );
        makePlaneTri( br, bl, tl );
      }

      vertIndex = max( bl, centre );
      lastBR[xInd] = br;

    }
  }

  // exit( 0 );
}

int ofxLoopinMesh::makePlaneVertex( float cx, float cy, int x, int y, int w, int h ) {

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
    ul + ( ur - ul ) * 0.5, // b
    vt + ( vb - vt ) * 0.5, // a
    w, h,       // nx, ny
    1 // nz
  );
};


void ofxLoopinMesh::makePlaneTri( ofIndexType a, ofIndexType b, ofIndexType c ) {
  vector<ofIndexType> & meshIndices = _mesh.getIndices();
  meshIndices.push_back( a );
  meshIndices.push_back( b );
  meshIndices.push_back( c );
};

int ofxLoopinMesh::addVertex(
  float x, float y, float z,
  float u, float v,
  float r, float g, float b, float a,
  float nx, float ny, float nz )
{
  int ind = _mesh.getVertices().size();
  _mesh.getVertices().push_back( ofVec3f( x, y, z ) );
  _mesh.getTexCoords().push_back( ofVec2f( u, v ) );
  _mesh.getColors().push_back( ofFloatColor( r, g, b, a ) );
  _mesh.getNormals().push_back( ofVec3f( nx, ny, nz ) );
  return ind;
};


/**
## Scatter
*/
void ofxLoopinMesh::makeScatter( const Json::Value & val ) {
  int count = 256;
  int seed = -1;

  if ( val.isInt() ) {
    count = val.asInt();
  } else if ( val.isObject() ) {
    if ( val.isMember("count") && val["count"].isInt() )
      count = val["count"].asInt();

    if ( val.isMember("seed") && val["seed"].isInt() )
      seed = val["seed"].asInt();
  }

  makeScatter( count, seed );
}

void ofxLoopinMesh::makeScatter( int num, int seed ) {
  erase();
  mode.setKey("points");

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

//
// Cube
//

void ofxLoopinMesh::makeCube( const Json::Value & val ) {
  int count = 1;

  if ( val.isInt() ) {
    count = val.asInt();
  } else if ( val.isObject() ) {
    if ( val.isMember("count") && val["count"].isInt() ) count = val["count"].asInt();
  }

  makeCube( count );
}

void ofxLoopinMesh::makeCube( int count ) {
  erase();
  mode.setKey("triangles");

  for ( int cubeIndex = 0; cubeIndex < count; cubeIndex ++ ) {
    for ( int faceIndex = 0; faceIndex < 6; faceIndex ++ ) {
      makeCubeFace( cubeIndex, faceIndex );
    }
  }
}

void ofxLoopinMesh::makeCubeFace( int cubeIndex, int faceIndex ) {
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

  makePlaneTri( tl, tr, br );
  makePlaneTri( br, bl, tl );
}

int ofxLoopinMesh::makeCubeVertex( int cubeIndex, int faceIndex, ofVec3f normal, ofVec2f uv ) {

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
    0, // b
    1, // a
    normal.x, normal.y, normal.z
  );

}


//
// Other stuff
//

void ofxLoopinMesh::setIndices( const Json::Value & val ) {
  vector<ofIndexType> & meshIndices = _mesh.getIndices();

  if ( val.isArray() ) {
    size_t valLength = val.size();

    meshIndices.resize( valLength );

    for ( int valIndex = 0; valIndex < valLength; valIndex ++ ) {
      if ( val[valIndex].isInt() ) {
        int indexValue = val[valIndex].asInt();
        meshIndices[valIndex] = indexValue;
      }
    }
  }
}

void ofxLoopinMesh::setVertices( const Json::Value & val ) {
  if ( val.isArray() ) {
    for ( int valIndex = 0; valIndex < val.size(); valIndex ++ ) {
      setVertexElements( valIndex, val[valIndex] );
    }
  }

  if ( val.isObject() ) {
    for( Json::ValueIterator it = val.begin(); it != val.end() ; it++) {
      string key = it.key().asString();
      stringstream ss( key );
      int vertIndex = -1;
      ss >> vertIndex;
      if ( vertIndex != -1 )
        setVertexElements( vertIndex, *it );
    }
  }
}

void ofxLoopinMesh::setVertexElements( int vertIndex, const Json::Value &val ) {
  if ( val.isArray() ) {
    for ( int valIndex = 0; valIndex < val.size(); valIndex ++ ) {
      if ( val[valIndex].isNumeric() )
        setVertexElement( vertIndex, valIndex, val[valIndex].asFloat() );
    }
  }

  if ( val.isObject() ) {
    for( Json::ValueIterator it = val.begin(); it != val.end() ; it++) {
      if ( !(*it).isNumeric() )
        continue;

      float valFloat = (*it).asFloat();
      setVertexElement( vertIndex, vertexKeyToAxis( it.key().asString() ), valFloat );
    }
  }
}

int ofxLoopinMesh::vertexKeyToAxis( const string &key ) {
  if ( key == "x" || key == "0" ) return 0;
  if ( key == "y" || key == "1" ) return 1;
  if ( key == "z" || key == "2" ) return 2;
  if ( key == "u" || key == "3" ) return 3;
  if ( key == "v" || key == "4" ) return 4;
  if ( key == "r" || key == "5" ) return 5;
  if ( key == "g" || key == "6" ) return 6;
  if ( key == "b" || key == "7" ) return 7;
  if ( key == "a" || key == "8" ) return 8;
  if ( key == "nx" || key == "9" ) return 9;
  if ( key == "ny" || key == "10" ) return 10;
  if ( key == "nz" || key == "11" ) return 11;

  return -1;
}

// vert x: 0
// vert y: 1
// vert z: 2
// tex  x: 3
// tex  y: 4
// color r: 5
// color g: 6
// color b: 7
// color a: 8
// normal x: 9
// normal y: 10
// normal z: 11
void ofxLoopinMesh::setVertexElement( int index, int axis, float value ) {
  if ( axis < 0 ) {
    // Unknown axis
  } else if ( axis < 3 ) {
    // xyz vertex
    vector<ofVec3f> &vertices = _mesh.getVertices();
    if ( index >= vertices.size() )
      vertices.resize( index + 1 );

    vertices[index][axis] = value;
  } else if ( axis < 5 ) {
    // uv texCoords
    vector<ofVec2f> &texCoords = _mesh.getTexCoords();
    if ( index >= texCoords.size() )
      texCoords.resize( index + 1 );

    texCoords[index][axis - 3] = value;
  } else if ( axis < 9 ) {
    // rgba colour
    vector<ofFloatColor> &colours = _mesh.getColors();
    if ( index >= colours.size() )
      colours.resize( index + 1  );

    colours[index][axis - 5] = value;
  } else if ( axis < 12 ) {
    // xyz normal
    vector<ofVec3f> &normals = _mesh.getNormals();
    if ( index >= normals.size() )
      normals.resize( index + 1  );

    normals[index][axis - 9] = value;
  }
}
