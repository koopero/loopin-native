#include "ofxLoopinShader.h"

void ofxLoopinShader::patchLocalAfter( const Json::Value & value ) {
  refresh( false );
};

void ofxLoopinShader::addSubControls() {
  addSubControl("vert", &vert );
  addSubControl("frag", &frag );
};

void ofxLoopinShader::refresh( bool sendNeedEvent ) {
  ofxLoopinEvent event;

  if ( !_initialized ) {
    cerr << "INIT SHADER" << endl;
    vert.key = "vert";
    frag.key = "frag";
    vert.loadDefault();
    frag.loadDefault();
    if ( sendNeedEvent ) {
      event.type = "need";
      dispatch( event );
    }
    _initialized = true;
  }


  vert.load();
  frag.load();

  if ( vert.isDataReady() && frag.isDataReady() ) {
    if ( vert.dataIsNew || frag.dataIsNew ) {

      vert.dataIsNew = false;
      frag.dataIsNew = false;

      event.type = "captureStart";
      dispatch( event );

      shader.setupShaderFromSource( GL_VERTEX_SHADER, vert.data );
      shader.setupShaderFromSource( GL_FRAGMENT_SHADER, frag.data );
      shader.bindDefaults();
      shader.linkProgram();

      event.type = "captureEnd";
      dispatch( event );

      event.type = "done";
      // event.data["_vertData"] = vert.data;
      dispatch( event );
    }
  }
}

void ofxLoopinShader::begin() {
  refresh();
  shader.begin();
  _textureLocation = 1;
}

void ofxLoopinShader::end() {
  shader.end();
}

void ofxLoopinShader::applyUniformsPass( int passIndex, int passTotal ) {
  // cerr << "applyUniformsPass " << passIndex << " " << passTotal << endl;
  shader.setUniform1i( "passIndex", passIndex );
  shader.setUniform1i( "passTotal", passTotal );
  shader.setUniform1f( "passDensity", 1.0 / (float) passTotal );
  shader.setUniform1f( "passX", (float) passIndex / (float) passTotal );
}

void ofxLoopinShader::applyUniformsBuffer( ofxLoopinBuffer * buffer ) {
  shader.setUniform1f( "bufferAspect", buffer->getAspect() );
  shader.setUniform1i( "bufferWidth", buffer->getWidth() );
  shader.setUniform1i( "bufferHeight", buffer->getHeight() );
  shader.setUniform1i( "bufferRows", buffer->rows.getValueInt() );
  shader.setUniform1i( "bufferCols", buffer->cols.getValueInt() );
}

void ofxLoopinShader::applyUniformsMesh( ofxLoopinMeshBase * mesh ) {
  shader.setUniform1f( "meshAspect", mesh->aspect );
  shader.setUniform1i( "meshCount", mesh->meta_count );
  shader.setUniform1i( "meshRows", mesh->meta_rows );
  shader.setUniform1i( "meshCols", mesh->meta_cols );
}

void ofxLoopinShader::applyUniformsGlobalClock() {
  ofxLoopinFrame frame = root->frame;
  shader.setUniform1i( "clockGlobalIndex", frame.index );
  shader.setUniform1f( "clockGlobalTime", frame.time );
  shader.setUniform1f( "clockGlobalDelta", frame.delta );
}


void ofxLoopinShader::applyUniformsFrame() {
  ofxLoopinFrame frame = root->frame;
  shader.setUniform1i( "clockIndex", frame.index );
  shader.setUniform1f( "clockTime", frame.time );
  shader.setUniform1f( "clockDelta", frame.delta );
}

void ofxLoopinShader::applyUniformPointSize( float pointSize ) {
  shader.setUniform1f( "pointSize", pointSize );
  shader.setUniform1f( "pointDensity", 1.0 / pointSize / pointSize );
}
