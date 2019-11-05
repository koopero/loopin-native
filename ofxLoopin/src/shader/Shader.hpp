#pragma once

#include "./control/Control.hpp"
#include "../mesh/MeshBase.hpp"
#include "../clock/Frame.hpp"
#include "./ShaderElement.hpp"

#include "ofShader.h"

/** loopin/type/shader
sub:
  vert:
    type: shaderElement

  frag:
    type: shaderElement
*/
namespace ofxLoopin { namespace shader {
class Shader : public ofxLoopin::control::Control {
public:
  Shader() {};
  Shader( string _key ) {
    key = _key;
  };

  Shader( string _key, string defaultFragSource ) {
    key = _key;
    frag.data = defaultFragSource;
    frag.dataIsNew = true;
  };

  Shader( string _key, string defaultVertSource, string defaultFragSource ) {
    key = _key;
    frag.data = defaultFragSource;
    frag.dataIsNew = true;
    vert.data = defaultVertSource;
    vert.dataIsNew = true;
  };

  ofShader shader;

  ShaderElement vert;
  ShaderElement frag;

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
  void applyUniformsBuffer( ofxLoopin::base::Buffer * buffer );
  void applyUniformsMesh( ofxLoopin::mesh::MeshBase * mesh );
  void applyUniformsFrame();
  void applyUniformPointSize( float pointSize );
  void applyUniformsGlobalClock();

protected:
  void refresh( bool sendNeedEvent = true );
  void addSubControls();
  void patchLocalAfter( const ofJson & value );

  bool _initialized = false;
};
}};