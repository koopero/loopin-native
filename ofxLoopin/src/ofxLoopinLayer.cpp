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

  renderSelf( buffer );

  layers.render( renderingFrame, buffer );

}

void ofxLoopinLayer::renderSelf( ofxLoopinBuffer * buffer )  {
  ofxLoopinShader * shader = ofxLoopinLayer::shader.getPointer();
  ofxLoopinMesh * mesh = ofxLoopinLayer::mesh.getPointer();
  ofxLoopinCamera * camera = ofxLoopinLayer::camera.getPointer();

  float pointSize = ofxLoopinLayer::pointSize;

  if ( !shader ) { dispatch("shaderFault"); return; }
  if ( !mesh ) { dispatch("meshFault"); return; }
  if ( !camera ) { dispatch("cameraFault"); return; }

  auto renderer = ofGetCurrentRenderer();

  shader->begin();
  shader->applyUniformsDefaults();
  shader->applyUniformsGlobalClock();
  shader->applyUniformPointSize( pointSize );
  shader->applyUniformsBuffer( buffer );

  clockControl.applyUniforms( shader->shader );

  uniforms.bindToShader( shader );

  if ( pointSize > 0.0 ) {
    ofEnablePointSprites();
    glPointSize( pointSize );
  } else {
    ofDisablePointSprites();
  }

  ofEnableBlendMode( blend.getEnumValue() );
  ofSetDepthTest( ofxLoopinLayer::depthTest.getValue() );

  //
  // Set Aspects
  //
  camera->setLayerAspect( ofxLoopinLayer::aspect );
  camera->setBufferAspect( buffer->getArea(), buffer->aspect );
  camera->setMeshAspect( mesh->aspect );
  camera->setTransform( transform );

  camera->calculate();

  camera->setUniforms( shader );

  //
  // Set Matrixs
  //


  GLenum face_ = face.getEnumValue();

  // if ( face_ ) {
  //   glEnable( GL_CULL_FACE );
  //   glCullFace( face_ );
  //   glFrontFace( GL_CW );
  // } else {
  //   glDisable( GL_CULL_FACE );
  // }

  for ( int pass = 0; pass < passes; pass ++ ) {
    buffer->begin();

    if ( !pass ) {
      if ( (bool) ofxLoopinLayer::clear ) {
        ofClear( 0, 0, 0, 0 );

        #ifndef TARGET_OPENGLES
          glClearDepth(1000);
        #endif
      }
    }
    camera->loadMatrixes();

    shader->applyUniformsPass( pass, passes );
    mesh->draw();

    buffer->end();
  }

  glDisable( GL_CULL_FACE );
  ofDisablePointSprites();
  ofSetDepthTest( false );

  buffer->end();
  shader->end();

  uniforms.unbind();
}
