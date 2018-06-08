#include "ofxLoopinMeshBase.h"

void ofxLoopinMeshBase::setModeTriangles() {
  mode.setKey("triangles");

}
void ofxLoopinMeshBase::setModePoints() {
  mode.setKey("points");
}

void ofxLoopinMeshBase::erase() {
  _mesh.getIndices().resize(0);
  _mesh.getVertices().resize(0);
  _mesh.getTexCoords().resize(0);
  _mesh.getColors().resize(0);
  _mesh.getNormals().resize(0);
};

int ofxLoopinMeshBase::addVertex(
  float x, float y, float z,
  float u, float v,
  float r, float g, float b, float a,
  float nx, float ny, float nz )
{
  int ind = _mesh.getVertices().size();

  // std::cerr << "addVertex " << ind << " " << roundf(x*100.0)/100.0 << " " << roundf(y*100.0)/100.0 << endl;

  _mesh.getVertices().push_back( ofVec3f( x, y, z ) );
  _mesh.getTexCoords().push_back( ofVec2f( u, v ) );
  _mesh.getColors().push_back( ofFloatColor( r, g, b, a ) );
  _mesh.getNormals().push_back( ofVec3f( nx, ny, nz ) );
  return ind;
};



void ofxLoopinMeshBase::addTriangle( ofIndexType a, ofIndexType b, ofIndexType c ) {
  // std::cerr << "addTriangle " << a << " " << b << " " << c << endl;

  std::vector<ofIndexType> & meshIndices = _mesh.getIndices();
  meshIndices.push_back( a );
  meshIndices.push_back( b );
  meshIndices.push_back( c );
};

//
// Other stuff
//

void ofxLoopinMeshBase::setIndices( const ofJson & val ) {
  if ( val.is_array() ) {
    std::vector<ofIndexType> & meshIndices = _mesh.getIndices();
    meshIndices.resize( val.size() );
  }

  if ( val.is_object() || val.is_array() ) {
    for( auto it = val.begin(); it != val.end() ; it++) {
      string key = it.key();
      std::stringstream ss( key );
      int index = -1;
      ss >> index;
      if ( index != -1 )
        setIndex( index, *it );
    }
  }
}

void ofxLoopinMeshBase::setIndex( int index, const ofJson & val ) {
  std::vector<ofIndexType> & meshIndices = _mesh.getIndices();

  if ( index >= meshIndices.size() )
    meshIndices.resize( index + 1 );

  if ( val.is_number() ) {
    int indexValue = val.get<int>();
    meshIndices[index] = indexValue;
  }
}

void ofxLoopinMeshBase::setVertices( const ofJson & val ) {
  if ( val.is_array() ) {
    for ( int valIndex = 0; valIndex < val.size(); valIndex ++ ) {
      setVertexElements( valIndex, val[valIndex] );
    }
  }

  if ( val.is_object() ) {
    for( auto it = val.begin(); it != val.end() ; it++) {
      string key = it.key();
      std::stringstream ss( key );
      int vertIndex = -1;
      ss >> vertIndex;
      if ( vertIndex != -1 )
        setVertexElements( vertIndex, *it );
    }
  }
}

void ofxLoopinMeshBase::setVertexElements( int vertIndex, const ofJson & val ) {
  if ( val.is_array() ) {
    for ( int valIndex = 0; valIndex < val.size(); valIndex ++ ) {
      if ( val[valIndex].is_number() )
        setVertexElement( vertIndex, valIndex, val[valIndex].get<float>() );
    }
  }

  if ( val.is_object() ) {
    for( auto it = val.begin(); it != val.end() ; it++) {
      if ( !(*it).is_number() )
        continue;

      float valFloat = (*it).get<float>();
      setVertexElement( vertIndex, vertexKeyToAxis( it.key() ), valFloat );
    }
  }
}

int ofxLoopinMeshBase::vertexKeyToAxis( const string &key ) {
  if ( key == "x" || key == "0" ) return 0;
  if ( key == "y" || key == "1" ) return 1;
  if ( key == "z" || key == "2" ) return 2;
  if ( key == "u" || key == "3" ) return 3;
  if ( key == "v" || key == "4" ) return 4;
  if ( key == "r" || key == "red" || key == "5" ) return 5;
  if ( key == "g" || key == "green" || key == "6" ) return 6;
  if ( key == "b" || key == "blue" || key == "7" ) return 7;
  if ( key == "a" || key == "alpha" || key == "8" ) return 8;
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
void ofxLoopinMeshBase::setVertexElement( int index, int axis, float value ) {
  if ( axis < 0 ) {
    // Unknown axis
  } else if ( axis < 3 ) {
    // xyz vertex
    // std::vector<ofVec3f> &vertices = _mesh.getVertices();
    auto &vertices = _mesh.getVertices();
    
    if ( index >= vertices.size() )
      vertices.resize( index + 1 );

    vertices[index][axis] = value;
  } else if ( axis < 5 ) {
    // uv texCoords
    auto &texCoords = _mesh.getTexCoords();
    if ( index >= texCoords.size() )
      texCoords.resize( index + 1 );

    texCoords[index][axis - 3] = value;
  } else if ( axis < 9 ) {
    // rgba colour
    auto &colours = _mesh.getColors();
    if ( index >= colours.size() )
      colours.resize( index + 1  );

    colours[index][axis - 5] = value;
  } else if ( axis < 12 ) {
    // xyz normal
    auto &normals = _mesh.getNormals();
    if ( index >= normals.size() )
      normals.resize( index + 1  );

    normals[index][axis - 9] = value;
  }
}
