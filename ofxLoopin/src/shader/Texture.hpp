#pragma once

#include "../base/Buffer.hpp"
#include "../control/Control.hpp"
#include "../control/Reference.hpp"
#include "../options/Filter.hpp"
#include "../options/Wrap.hpp"
#include "../shader/Shader.hpp"
#include "./Uniform.hpp"

namespace ofxLoopin { namespace shader {
class Texture : public ofxLoopin::control::Control, public Uniform {
public:

  ofxLoopin::control::Reference<ofxLoopin::base::Buffer,ofxLoopin::base::HasBuffers> buffer;

  options::Filter minFilter;
  options::Filter magFilter;

  options::Wrap wrapH;
  options::Wrap wrapV;

  bool hasTexture();
  ofTexture * getTexture();


  void bindToShader( ofxLoopin::shader::Shader * shader ) override;
  void renderTexture( ofxLoopin::shader::Shader * shader, const ofRectangle & bounds );

  void unbind() override;
  void bindTexture( ofTexture * texture );

protected:
  virtual void patchString( string value ) override;
  virtual void patchLocal( const ofJson & value ) override;

  virtual void addSubControls() override;

  int _boundLocation = -1;
  string _bufferDescription;
  ofxLoopin::shader::Shader * _shader = nullptr;
  ofTexture * _texture = nullptr;
};
}};