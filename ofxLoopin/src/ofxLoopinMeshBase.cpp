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

  // cerr << "addVertex " << ind << " " << roundf(x*100.0)/100.0 << " " << roundf(y*100.0)/100.0 << endl;

  _mesh.getVertices().push_back( ofVec3f( x, y, z ) );
  _mesh.getTexCoords().push_back( ofVec2f( u, v ) );
  _mesh.getColors().push_back( ofFloatColor( r, g, b, a ) );
  _mesh.getNormals().push_back( ofVec3f( nx, ny, nz ) );
  return ind;
};



void ofxLoopinMeshBase::addTriangle( ofIndexType a, ofIndexType b, ofIndexType c ) {
  // cerr << "addTriangle " << a << " " << b << " " << c << endl;

  vector<ofIndexType> & meshIndices = _mesh.getIndices();
  meshIndices.push_back( a );
  meshIndices.push_back( b );
  meshIndices.push_back( c );
};

//
// Other stuff
//

void ofxLoopinMeshBase::setIndices( const Json::Value & val ) {
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

void ofxLoopinMeshBase::setVertices( const Json::Value & val ) {
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

void ofxLoopinMeshBase::setVertexElements( int vertIndex, const Json::Value &val ) {
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
