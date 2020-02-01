#include "./Layer.hpp"

#include <assert.h>

void ofxLoopin::render::Layer::addSubControls() {
  _needAdvance = true;
  ofxLoopin::render::Blit::addSubControls();
  addSubControl( "mesh", &mesh );
  addSubControl( "camera", &camera );
  addSubControl( "transform", &transform );

  src = uniforms.textures.getByKey("src", true );
  addSubControl( "src", src );

  /** loopin/type/layer/sub/layer
    map: layer
  */
  addSubControl( "layer", &layers );

  /** loopin/type/layer/sub/face
    options:
      - both
      - front
      - back
  */
  face.enumAddOption("both", 0 );
  face.enumAddOption("front", GL_FRONT );
  face.enumAddOption("back", GL_BACK );
  addSubControl( "face", &face );

  addSubControl( "passes", &passes );
  addSubControl( "pointSize", &pointSize );

  addSubControl( "depth", &depthTest );
  addSubControl( "aspect", &aspect );
  addSubControl( "order", &order );
}


void ofxLoopin::render::Layer::renderSelf( )  {
  for ( int pass = 0; pass < passes; pass ++ ) {
    if ( pass > 0 ) {
      if ( passAdvance ) {
        _buffer->end();
        _buffer->flip();
        _buffer->begin();
        renderStyle();
        renderUniforms();
      }
    }
    renderUniformsPerPass( pass );
    _camera->loadMatrixes();
    _mesh->draw();
  }
};

bool ofxLoopin::render::Layer::renderSetup() {
  if ( !ofxLoopin::render::Blit::renderSetup() )
    return false; 

  _mesh = ofxLoopin::render::Layer::mesh.getPointer();
  _camera = ofxLoopin::render::Layer::camera.getPointer();

  if ( !_mesh ) { dispatch("meshFault"); return false; }
  if ( !_camera ) { dispatch("cameraFault"); return false; }

  return true;
}

void ofxLoopin::render::Layer::renderUniforms() {
  ofxLoopin::render::Blit::renderUniforms();

  _shader->applyUniformPointSize( pointSize );
  _shader->applyUniformsMesh( _mesh );
  //
  // Set Aspects
  //
  _camera->setLayerAspect( ofxLoopin::render::Layer::aspect );
  _camera->setBufferAspect( _buffer->getArea(), _buffer->aspect );
  _camera->setMeshAspect( _mesh->aspect );
  _camera->setTransform( transform );
  _camera->calculate();
  _camera->setUniforms( _shader );
}

void ofxLoopin::render::Layer::renderStyle() {
  float pointSize = ofxLoopin::render::Layer::pointSize;

  // cerr << "Layer::renderStyle:: " << path << " " << pointSize << endl;

  if ( pointSize > 0.0 ) {
    ofEnablePointSprites();
    glPointSize( pointSize );
  } else {
    glPointSize( 1 );
    ofDisablePointSprites();
  }

  // ofEnableBlendMode( blend.getEnumValue() );
  blend.apply();
  ofSetDepthTest( ofxLoopin::render::Layer::depthTest.getValue() );

  GLenum face_ = face.getEnumValue();

  if ( face_ ) {
    glEnable( GL_CULL_FACE );
    glCullFace( face_ );
    glFrontFace( GL_CW );
  } else {
    glDisable( GL_CULL_FACE );
  }
}

void ofxLoopin::render::Layer::renderUniformsPerPass( int pass ) {
  _shader->applyUniformsPass( pass, passes );
};
