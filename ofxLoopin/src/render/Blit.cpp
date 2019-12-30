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

  _buffer = buffer;

  renderClear();

  if ( renderSetup() )
    renderSelf();
}

void ofxLoopin::render::Blit::renderClear()  {
  if ( !_buffer ) return;
  
  if ( clear.shouldClear( _buffer->bufferIsNew ) ) {
    _buffer->begin();
    clear.renderClear();
    _buffer->end();
    _buffer->bufferIsNew = false;
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


bool ofxLoopin::render::Blit::renderSetup() {
  _shader = shader.getPointer();
  if ( !_shader ) { dispatch("shaderFault"); return false; }

  return true;
}