#include "./shader/Shader.hpp"

void ofxLoopin::shader::Shader::patchLocalAfter( const ofJson & value ) {
  refresh( false );
};

void ofxLoopin::shader::Shader::addSubControls() {
  addSubControl("vert", &vert );
  addSubControl("frag", &frag );
};

void ofxLoopin::shader::Shader::refresh( bool sendNeedEvent ) {
  ofxLoopin::control::Event event;

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

void ofxLoopin::shader::Shader::begin() {
  refresh();
  shader.begin();
  _textureLocation = 1;
}

void ofxLoopin::shader::Shader::end() {
  shader.end();
}

void ofxLoopin::shader::Shader::applyUniformFloat( const string & name, double value ) {
  shader.setUniform1f( name, value );
}

void ofxLoopin::shader::Shader::applyUniformInt( const string & name, int value ){
  shader.setUniform1i( name, value );
}

void ofxLoopin::shader::Shader::applyUniformVec2( const string & name, ofVec2f value ){
  shader.setUniform2f( name, value );
}

void ofxLoopin::shader::Shader::applyUniformVec3( const string & name, ofVec3f value ){
  shader.setUniform3f( name, value );
}

void ofxLoopin::shader::Shader::applyUniformVec4( const string & name, ofVec4f value ){
  shader.setUniform4f( name, value );
}

void ofxLoopin::shader::Shader::applyUniformsPass( int passIndex, int passTotal ) {
  // std::cerr << "applyUniformsPass " << passIndex << " " << passTotal << endl;
  applyUniformInt( "passIndex", passIndex );
  applyUniformInt( "passTotal", passTotal );
  applyUniformFloat( "passDensity", 1.0 / (float) passTotal );
  applyUniformFloat( "passX", (float) passIndex / (float) passTotal );
}

void ofxLoopin::shader::Shader::applyUniformsBuffer( ofxLoopinBuffer * buffer ) {
  applyUniformFloat( "bufferAspect", buffer->getAspect() );
  applyUniformInt( "bufferWidth", buffer->getWidth() );
  applyUniformInt( "bufferHeight", buffer->getHeight() );
  applyUniformInt( "bufferRows", buffer->rows.getValueInt() );
  applyUniformInt( "bufferCols", buffer->cols.getValueInt() );
}

void ofxLoopin::shader::Shader::applyUniformsMesh( mesh::MeshBase * mesh ) {
  applyUniformFloat( "meshAspect", mesh->aspect );
  applyUniformInt( "meshCount", mesh->meta_count );
  applyUniformInt( "meshRows", mesh->meta_rows );
  applyUniformInt( "meshCols", mesh->meta_cols );
}

void ofxLoopin::shader::Shader::applyUniformsGlobalClock() {
  ofxLoopin::clock::Frame frame = root->frame;
  applyUniformInt( "clockGlobalIndex", frame.index );
  applyUniformFloat( "clockGlobalTime", frame.time );
  applyUniformFloat( "clockGlobalDelta", frame.delta );
}


void ofxLoopin::shader::Shader::applyUniformsFrame() {
  ofxLoopin::clock::Frame frame = root->frame;
  applyUniformInt( "clockIndex", frame.index );
  applyUniformFloat( "clockTime", frame.time );
  applyUniformFloat( "clockDelta", frame.delta );
}

void ofxLoopin::shader::Shader::applyUniformPointSize( float pointSize ) {
  applyUniformFloat( "pointSize", pointSize );
  applyUniformFloat( "pointDensity", 1.0 / pointSize / pointSize );
}
