#include "ofxLoopinLayer.h"

#include <assert.h>

void ofxLoopinLayer::renderBuffer( ofxLoopinBuffer * buffer )  {

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
    ofxLoopinEvent e = ofxLoopinEvent("bufferFault");
    dispatch( e );
    return;
  }

  _buffer = buffer;

  renderClear();

  if ( passes > 0 && renderSetup() )
    renderSelf();

  layers.render( renderingFrame, buffer );

}

void ofxLoopinLayer::renderClear()  {
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


void ofxLoopinLayer::renderSelf( )  {
  _buffer->begin();
  _shader->begin();

  renderUniforms();
  renderStyle();

  for ( int pass = 0; pass < passes; pass ++ ) {
    if ( pass > 0 ) {

      if ( passAdvance ) {
        _buffer->flip();
      }

      _buffer->begin();
      renderUniformsPerPass( pass );
    }

    _camera->loadMatrixes();

    _mesh->draw();
    _buffer->end();
  }



  _buffer->end();
  _shader->end();

  resetStyle();
  resetUniforms();

};

bool ofxLoopinLayer::renderSetup() {
  _shader = ofxLoopinLayer::shader.getPointer();
  _mesh = ofxLoopinLayer::mesh.getPointer();
  _camera = ofxLoopinLayer::camera.getPointer();

  if ( !_shader ) { dispatch("shaderFault"); return false; }
  if ( !_mesh ) { dispatch("meshFault"); return false; }
  if ( !_camera ) { dispatch("cameraFault"); return false; }

  return true;
}

void ofxLoopinLayer::renderUniforms() {
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
  _camera->setLayerAspect( ofxLoopinLayer::aspect );
  _camera->setBufferAspect( _buffer->getArea(), _buffer->aspect );
  _camera->setMeshAspect( _mesh->aspect );
  _camera->setTransform( transform );
  _camera->calculate();
  _camera->setUniforms( _shader );
}

void ofxLoopinLayer::renderStyle() {
  float pointSize = ofxLoopinLayer::pointSize;
  if ( pointSize > 0.0 ) {
    ofEnablePointSprites();
    glPointSize( pointSize );
  } else {
    ofDisablePointSprites();
  }

  ofEnableBlendMode( blend.getEnumValue() );
  ofSetDepthTest( ofxLoopinLayer::depthTest.getValue() );

  GLenum face_ = face.getEnumValue();

  if ( face_ ) {
    glEnable( GL_CULL_FACE );
    glCullFace( face_ );
    glFrontFace( GL_CW );
  } else {
    glDisable( GL_CULL_FACE );
  }
}

void ofxLoopinLayer::resetStyle() {
  glDisable( GL_CULL_FACE );
  ofDisablePointSprites();
  ofSetDepthTest( false );
}

void ofxLoopinLayer::resetUniforms() {
  uniforms.unbind();

}

void ofxLoopinLayer::renderUniformsPerPass( int pass ) {
  _shader->applyUniformsPass( pass, passes );
};
