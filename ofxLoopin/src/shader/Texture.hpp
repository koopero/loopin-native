#pragma once

#include "../base/Buffer.hpp"
#include "./control/Control.hpp"
#include "./control/Reference.hpp"
#include "./options/Filter.hpp"
#include "./options/Wrap.hpp"
#include "./shader/Shader.hpp"
#include "./Uniform.hpp"

namespace ofxLoopin { namespace shader {
class Texture : public ofxLoopin::control::Control, public Uniform {
public:

  ofxLoopin::control::Reference<ofxLoopin::base::Buffer,ofxLoopin::base::HasBuffers> buffer;

  options::Filter minFilter;
  options::Filter magFilter;

  options::Wrap wrapH;
  options::Wrap wrapV;


  bool hasTexture() {
    ofxLoopin::base::Buffer * bufferP = buffer.getPointer();
    if ( bufferP ) {
      return bufferP->isAllocated();
    }

    return false;
  }

  void bindToShader( ofxLoopin::shader::Shader * shader ) override;
  void bindSpecific( ofxLoopin::shader::Shader * shader, string key, int location );
  void unbind() override;


protected:
  virtual void patchString( string value ) override;
  virtual void patchLocal( const ofJson & value ) override;

  virtual void addSubControls();

  int _boundLocation = -1;
};
}};