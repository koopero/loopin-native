#include "ofxLoopinShader.h"

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
