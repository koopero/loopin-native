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
    vert.key = "vert";
    frag.key = "frag";
    vert.loadDefault();
    frag.loadDefault();
    if ( sendNeedEvent ) {
      event.type = "need";
      if( root ) dispatch( event );
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
      if ( root ) dispatch( event );

      shader.setupShaderFromSource( GL_VERTEX_SHADER, vert.data );
      shader.setupShaderFromSource( GL_FRAGMENT_SHADER, frag.data );
      shader.bindDefaults();
      shader.linkProgram();

      event.type = "captureEnd";
      if ( root ) dispatch( event );

      event.type = "done";
      // event.data["_vertData"] = vert.data;
      if ( root ) dispatch( event );
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

void ofxLoopinShader::applyUniformFloat( const string & name, double value ) {
  shader.setUniform1f( name, value );
}

void ofxLoopinShader::applyUniformInt( const string & name, int value ){
  shader.setUniform1i( name, value );
}

void ofxLoopinShader::applyUniformsPass( int passIndex, int passTotal ) {
  // cerr << "applyUniformsPass " << passIndex << " " << passTotal << endl;
  applyUniformInt( "passIndex", passIndex );
  applyUniformInt( "passTotal", passTotal );
  applyUniformFloat( "passDensity", 1.0 / (float) passTotal );
  applyUniformFloat( "passX", (float) passIndex / (float) passTotal );
}

void ofxLoopinShader::applyUniformsBuffer( ofxLoopinBuffer * buffer ) {
  applyUniformFloat( "bufferAspect", buffer->getAspect() );
  applyUniformInt( "bufferWidth", buffer->getWidth() );
  applyUniformInt( "bufferHeight", buffer->getHeight() );
  applyUniformInt( "bufferRows", buffer->rows.getValueInt() );
  applyUniformInt( "bufferCols", buffer->cols.getValueInt() );
}

void ofxLoopinShader::applyUniformsMesh( ofxLoopinMeshBase * mesh ) {
  applyUniformFloat( "meshAspect", mesh->aspect );
  applyUniformInt( "meshCount", mesh->meta_count );
  applyUniformInt( "meshRows", mesh->meta_rows );
  applyUniformInt( "meshCols", mesh->meta_cols );
}

void ofxLoopinShader::applyUniformsGlobalClock() {
  ofxLoopinFrame frame = root->frame;
  applyUniformInt( "clockGlobalIndex", frame.index );
  applyUniformFloat( "clockGlobalTime", frame.time );
  applyUniformFloat( "clockGlobalDelta", frame.delta );
}


void ofxLoopinShader::applyUniformsFrame() {
  ofxLoopinFrame frame = root->frame;
  applyUniformInt( "clockIndex", frame.index );
  applyUniformFloat( "clockTime", frame.time );
  applyUniformFloat( "clockDelta", frame.delta );
}

void ofxLoopinShader::applyUniformPointSize( float pointSize ) {
  applyUniformFloat( "pointSize", pointSize );
  applyUniformFloat( "pointDensity", 1.0 / pointSize / pointSize );
}
