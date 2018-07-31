#include "ofxLoopinShaderElement.h"
#include "ofxLoopinFile.h"
#include "ofxLoopinShaderDefaults.h"


void ofxLoopinShaderElement::loadDefault() {
  // Already got data from ofxLoopinShader constructor
  if ( data.size() )
    return;

  if ( !file.size() )
    file = findDefaultFile();

  if ( !file.size() ) {
    if ( key == "vert" ) {
      #ifdef TARGET_OPENGLES
        data = ofxLoopinShaderDefaults::GLES_VERT;
      #else
        data = ofxLoopinShaderDefaults::GL_VERT;
      #endif
    } else if ( key == "frag" ) {
      #ifdef TARGET_OPENGLES
        data = ofxLoopinShaderDefaults::GLES_FRAG;
      #else
        data = ofxLoopinShaderDefaults::GL_FRAG;
      #endif
    }
  }

  dataIsNew = true;
}

string ofxLoopinShaderElement::findDefaultFile() {

  #ifdef TARGET_OPENGLES
  string version = "es";
  #else
  string version = "150";
  #endif
  std::vector<string> extensions;

  string file;
  string type = key;

  // shader/foo.150.frag
  file = ofxLoopinFile::find( "shader/"+key+"."+version+"."+type );
  if ( file.size() ) return file;

  // shader/foo.frag
  file = ofxLoopinFile::find( "shader/"+key+"."+type );
  if ( file.size() ) return file;

  // shader/foo.150.glsl
  file = ofxLoopinFile::find( "shader/"+key+"."+version+".glsl" );
  if ( file.size() ) return file;

  // shader/foo.glsl
  file = ofxLoopinFile::find( "shader/"+key+".glsl" );
  if ( file.size() ) return file;

  return "";
}

void ofxLoopinShaderElement::load() {
  if ( _loadedFile == file )
    return;

  if ( !file.size() )
    return;

  string absPath = ofxLoopinFile::find( file );

  if ( !absPath.size() ) {
    // TODO: Error here
    _loadedFile = file;
    auto errorEvent = ofxLoopinEvent::fileNotFound( filePath );

    dispatch( errorEvent );
    return;
  }

  _loadedFile = file;

  ofBuffer buffer = ofBufferFromFile( absPath );
  data = buffer.getText();

  dataIsNew = true;


  ofxLoopinEvent event;
  event.type = "loadFile";
  event.data["file"] = absPath;
  // event.data["data"] = data;
  dispatch( event );
}
