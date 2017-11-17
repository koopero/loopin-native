#include "ofxLoopinShaderElement.h"
#include "ofxLoopinFile.h"

bool ofxLoopinShaderElement::isStringGLSL( const string & str ) {
  // TODO
  return false;
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
