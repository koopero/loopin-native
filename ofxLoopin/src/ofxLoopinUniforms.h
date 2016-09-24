#pragma once

#include "ofxLoopinControl.h"
#include "ofxLoopinControlNumeric.h"
#include "ofxLoopinMap.h"
#include "ofxLoopinShader.h"
#include "ofxLoopinTexture.h"
#include "ofxLoopinUniform.h"

template <class child_type>
class ofxLoopinUniforms : public ofxLoopinMap<child_type> {
public:
  void bindToShader( ofxLoopinShader * shader ) {
    for ( auto & it : ofxLoopinMap<child_type>::getMap() ) {
      const string & key = it.first;
      ofxLoopinUniform & uniform = it.second;

      GLint location = shader->shader.getUniformLocation( key );
      // cerr << "bindToShader " << key << " " << location << endl;
      if ( true || location != -1 ) {
        uniform.bindToShader( shader );
      }
    }
  };

  void unbind() {
    for ( auto & it : ofxLoopinMap<child_type>::getMap() ) {
      ofxLoopinUniform & uniform = it.second;
      uniform.unbind();
    }
  }

};

class ofxLoopinUniformSet : public ofxLoopinControl {
public:
  void bindToShader( ofxLoopinShader * shader ) {
    floats.bindToShader( shader );
    tex.bindToShader( shader );
  }

  void unbind() {
    tex.unbind();
  }


  ofxLoopinUniforms<ofxLoopinUniformFloat> floats;
  ofxLoopinUniforms<ofxLoopinTexture> tex;

protected:
  void addSubControls() {
    addSubControl( "float", &floats );
    addSubControl( "tex", &tex );
  }


private:


};
