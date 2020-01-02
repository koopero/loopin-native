#include "./Blit.hpp"

void ofxLoopin::render::Blit::renderBuffer( ofxLoopin::base::Buffer * buffer )  {
  if ( !enable.isEnabledOnce( true ) )
    return;

  if ( !buffer ) {
    buffer = getBuffer( true );
  }

  assert( buffer != nullptr );

  clockControl.advance( renderingFrame );
  renderingFrame = clockControl.frame;

  if ( advance.isEnabledOnce( false ) ) {
    buffer->flip();
  }

  buffer->defaultSize();

  if ( !buffer->ready() ) {
    ofxLoopin::control::Event e = ofxLoopin::control::Event("bufferFault");
    dispatch( e );
    return;
  }

  if ( !renderSetup() )
    return;


  _buffer = buffer;
  _buffer->begin();
  renderClear( _buffer->bufferIsNew );
  _shader->begin();
  _buffer->bufferIsNew = false;
  renderUniforms();
  renderStyle();
  renderSelf();

  _buffer->end();
  _shader->end();

  resetStyle();
  resetUniforms();

  renderAfter();
}

void ofxLoopin::render::Blit::renderClear( bool bufferIsNew )  {
  if ( clear.shouldClear( bufferIsNew ) ) {
    resetStyle();
    clear.renderClear();
  }
}

void ofxLoopin::render::Blit::renderUniforms() {
  if ( !_shader ) return;

  _shader->applyUniformsDefaults();
  _shader->applyUniformsGlobalClock();
  _shader->applyUniformsBuffer( _buffer );
  clockControl.applyUniforms( _shader->shader );
  uniforms.bindToShader( _shader );
}


void ofxLoopin::render::Blit::renderStyle() {
  blend.apply();
}


void ofxLoopin::render::Blit::resetStyle() {
  glDisable( GL_CULL_FACE );
  ofDisablePointSprites();
  ofSetDepthTest( false );
  glDisable( GL_BLEND );
}

void ofxLoopin::render::Blit::resetUniforms() {
  uniforms.unbind();
}


bool ofxLoopin::render::Blit::renderSetup() {
  _shader = shader.getPointer();
  if ( !_shader ) { dispatch("shaderFault"); return false; }

  return true;
}