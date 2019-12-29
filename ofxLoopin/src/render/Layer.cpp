#include "./Layer.hpp"

#include <assert.h>

void ofxLoopin::render::Layer::renderBuffer( ofxLoopin::base::Buffer * buffer )  {
  if ( !enable.isEnabledOnce() )
    return;

  if ( !buffer ) {
    buffer = getBuffer( true );
  }

  assert( buffer != nullptr );

  clockControl.advance( renderingFrame );
  renderingFrame = clockControl.frame;

  if ( advance ) {
    buffer->flip();
  }

  buffer->defaultSize();

  if ( !buffer->ready() ) {
    ofxLoopin::control::Event e = ofxLoopin::control::Event("bufferFault");
    dispatch( e );
    return;
  }

  _buffer = buffer;

  renderClear();

  if ( passes > 0 && renderSetup() )
    renderSelf();

  layers.render( renderingFrame, buffer );

}

void ofxLoopin::render::Layer::renderClear()  {
  if ( clear.getEnumValue() == NONE )
    return;

  _buffer->begin();
  ofDisableBlendMode();

  switch( clear.getEnumValue() ) {
    case BOTH:
      ofClear( 0, 0, 0, 0 );
      #ifndef TARGET_OPENGLES
        glClearDepth(1000);
      #endif
    break;

    case RGBA:
      ofClear( 0, 0, 0, 0 );
    break;

    case DEPTH:
      #ifndef TARGET_OPENGLES
        glClearDepth(1000);
      #endif
    break;

    case NONE:
    break;
  }

  _buffer->end();
}


void ofxLoopin::render::Layer::renderSelf( )  {
  _buffer->begin();
  _shader->begin();

  renderStyle();
  renderUniforms();

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

  _buffer->end();
  _shader->end();

  resetStyle();
  resetUniforms();

};

bool ofxLoopin::render::Layer::renderSetup() {
  _shader = ofxLoopin::render::Layer::shader.getPointer();
  _mesh = ofxLoopin::render::Layer::mesh.getPointer();
  _camera = ofxLoopin::render::Layer::camera.getPointer();

  if ( !_shader ) { dispatch("shaderFault"); return false; }
  if ( !_mesh ) { dispatch("meshFault"); return false; }
  if ( !_camera ) { dispatch("cameraFault"); return false; }

  return true;
}

void ofxLoopin::render::Layer::renderUniforms() {
  _shader->applyUniformsDefaults();
  _shader->applyUniformsGlobalClock();
  _shader->applyUniformPointSize( pointSize );
  _shader->applyUniformsBuffer( _buffer );
  _shader->applyUniformsMesh( _mesh );
  clockControl.applyUniforms( _shader->shader );
  uniforms.bindToShader( _shader );

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

void ofxLoopin::render::Layer::resetStyle() {
  glDisable( GL_CULL_FACE );
  ofDisablePointSprites();
  ofSetDepthTest( false );
}

void ofxLoopin::render::Layer::resetUniforms() {
  uniforms.unbind();

}

void ofxLoopin::render::Layer::renderUniformsPerPass( int pass ) {
  _shader->applyUniformsPass( pass, passes );
};