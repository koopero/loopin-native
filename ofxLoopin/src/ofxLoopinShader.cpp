#include "ofxLoopinShader.h"

void ofxLoopinShader::addSubControls() {

  string fragDefaultFile = ofxLoopinFile::find( "shader/"+key+".frag" );
  string vertDefaultFile = ofxLoopinFile::find( "shader/"+key+".vert" );

  if ( vertDefaultFile.size() ) {
    vert.file = vertDefaultFile;
  } else {
    #ifdef TARGET_OPENGLES
      vert.data = ofxLoopinShaderDefaults::GLES_VERT;
    #else
      vert.data = ofxLoopinShaderDefaults::GL_VERT;
    #endif
  }
  vert.dataIsNew = true;

  if ( fragDefaultFile.size() ) {
    frag.file = fragDefaultFile;
  } else {
    #ifdef TARGET_OPENGLES
      frag.data = ofxLoopinShaderDefaults::GLES_FRAG;
    #else
      frag.data = ofxLoopinShaderDefaults::GL_FRAG;
    #endif
  }
  frag.dataIsNew = true;

  addSubControl("vert", &vert );
  addSubControl("frag", &frag );
};

void ofxLoopinShader::refresh() {
  ofxLoopinEvent event;

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


      event.type = "shader";
      event.data["loaded"] = shader.isLoaded();
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
};

void ofxLoopinShader::applyUniformsBuffer( ofxLoopinBuffer * buffer ) {
  shader.setUniform1f( "bufferAspect", buffer->getAspect() );
  shader.setUniform1i( "bufferRows", buffer->rows.getValueInt() );
  shader.setUniform1i( "bufferCols", buffer->cols.getValueInt() );
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
