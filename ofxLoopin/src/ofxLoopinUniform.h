#pragma once

#include "./shader/Shader.hpp"
#include "./control/Numeric.hpp"
#include "./control/Vector.hpp"

class ofxLoopinUniform {
public:
  virtual void bindToShader( ofxLoopin::shader::Shader * shader ) {};
  virtual void unbind() {};

};

class ofxLoopinUniformFloat :
  public ofxLoopinUniform,
  public ofxLoopin::control::Numeric
{
public:
  void bindToShader( ofxLoopin::shader::Shader * shader ) {
    float value = getValueFloat();
    shader->applyUniformFloat( key, value );
  };
};

class ofxLoopinUniformInt :
  public ofxLoopinUniform,
  public ofxLoopin::control::Numeric
{
public:
  void bindToShader( ofxLoopin::shader::Shader * shader ) {
    int value = getValueInt();
    shader->applyUniformInt( key, value );
  };
};

class ofxLoopinUniformVec2 :
  public ofxLoopinUniform,
  public ofxLoopin::control::Vector<2>
{
public:
  void bindToShader( ofxLoopin::shader::Shader * shader ) {
    shader->applyUniformVec2( key, getValueVec2() );
  };
};

class ofxLoopinUniformVec3 :
  public ofxLoopinUniform,
  public ofxLoopin::control::Vector<3>
{
public:
  void bindToShader( ofxLoopin::shader::Shader * shader ) {
    shader->applyUniformVec3( key, getValueVec3() );
  };
};

class ofxLoopinUniformVec4 :
  public ofxLoopinUniform,
  public ofxLoopin::control::Vector<4>
{
public:
  void bindToShader( ofxLoopin::shader::Shader * shader ) {
    shader->applyUniformVec4( key, getValueVec4() );
  };
};
