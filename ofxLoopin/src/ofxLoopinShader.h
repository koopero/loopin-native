#pragma once

#include "ofxLoopinControl.h"
#include "ofxLoopinFile.h"
#include "ofxLoopinFrame.h"
#include "ofxLoopinMeshBase.h"
#include "ofxLoopinShaderElement.h"
#include "ofShader.h"

/** loopin/type/shader
sub:
  vert:
    type: shaderElement

  frag:
    type: shaderElement
*/

class ofxLoopinShader : public ofxLoopinControl {
public:
  ofxLoopinShader() {};
  ofxLoopinShader( string _key ) {
    key = _key;
  };

  ofxLoopinShader( string _key, string defaultFragSource ) {
    key = _key;
    frag.data = defaultFragSource;
    frag.dataIsNew = true;
  };

  ofxLoopinShader( string _key, string defaultVertSource, string defaultFragSource ) {
    key = _key;
    frag.data = defaultFragSource;
    frag.dataIsNew = true;
    vert.data = defaultVertSource;
    vert.dataIsNew = true;
  };


  ofShader shader;

  ofxLoopinShaderElement vert;
  ofxLoopinShaderElement frag;

  int _textureLocation;

  void begin();
  void end();


  void applyUniformsDefaults() {
    applyUniformsGlobal();
    applyUniformsSelf();
  };
  virtual void applyUniformsGlobal() {};
  virtual void applyUniformsSelf() {};
  void applyUniformFloat( const string & name, double value );
  void applyUniformInt( const string & name, int value );
  void applyUniformVec2( const string & name, ofVec2f value );
  void applyUniformVec3( const string & name, ofVec3f value );
  void applyUniformVec4( const string & name, ofVec4f value );
  void applyUniformsPass( int passIndex, int passTotal );
  void applyUniformsBuffer( ofxLoopinBuffer * buffer );
  void applyUniformsMesh( ofxLoopinMeshBase * mesh );
  void applyUniformPointSize( float pointSize );
  void applyUniformsGlobalClock();

protected:
  void refresh( bool sendNeedEvent = true );
  void addSubControls();
  void patchLocalAfter( const ofJson & value );

  bool _initialized = false;
};
