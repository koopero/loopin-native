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

  void applyUniformsDefaults() { /* TODO */ };
  void applyUniformsPass( int passIndex, int passTotal );
  void applyUniformsBuffer( ofxLoopinBuffer * buffer );
  void applyUniformsMesh( ofxLoopinMeshBase * mesh );

  void applyUniformsFrame();
  void applyUniformPointSize( float pointSize );
  void applyUniformsGlobalClock();

protected:
  void refresh( bool sendNeedEvent = true );
  void addSubControls();
  void patchLocalAfter( const Json::Value & value );

  bool _initialized = false;
};
