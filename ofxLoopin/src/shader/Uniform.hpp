#pragma once

#include "./shader/Shader.hpp"
#include "./control/Numeric.hpp"
#include "./control/Vector.hpp"

namespace ofxLoopin { namespace shader { 
class Uniform {
public:
  virtual void bindToShader( ofxLoopin::shader::Shader * shader ) {};
  virtual void unbind() {};
};

class UniformFloat :
  public Uniform,
  public ofxLoopin::control::Numeric
{
public:
  void bindToShader( ofxLoopin::shader::Shader * shader ) {
    float value = getValueFloat();
    shader->applyUniformFloat( key, value );
  };
};

class UniformInt :
  public Uniform,
  public ofxLoopin::control::Numeric
{
public:
  void bindToShader( ofxLoopin::shader::Shader * shader ) {
    int value = getValueInt();
    shader->applyUniformInt( key, value );
  };
};

class UniformVec2 :
  public Uniform,
  public ofxLoopin::control::Vector<2>
{
public:
  void bindToShader( ofxLoopin::shader::Shader * shader ) {
    shader->applyUniformVec2( key, getValueVec2() );
  };
};

class UniformVec3 :
  public Uniform,
  public ofxLoopin::control::Vector<3>
{
public:
  void bindToShader( ofxLoopin::shader::Shader * shader ) {
    shader->applyUniformVec3( key, getValueVec3() );
  };
};

class UniformVec4 :
  public Uniform,
  public ofxLoopin::control::Vector<4>
{
public:
  void bindToShader( ofxLoopin::shader::Shader * shader ) {
    shader->applyUniformVec4( key, getValueVec4() );
  };
};
}};