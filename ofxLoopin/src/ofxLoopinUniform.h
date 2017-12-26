#pragma once

#include "ofxLoopinShader.h"
#include "ofxLoopinControlNumeric.h"
#include "ofxLoopinControlVector.h"



class ofxLoopinUniform {
public:
  virtual void bindToShader( ofxLoopinShader * shader ) {};
  virtual void unbind() {};

};

class ofxLoopinUniformFloat :
  public ofxLoopinUniform,
  public ofxLoopinControlNumeric
{
public:
  void bindToShader( ofxLoopinShader * shader ) {
    float value = getValueFloat();
    shader->applyUniformFloat( key, value );
  };
};

class ofxLoopinUniformInt :
  public ofxLoopinUniform,
  public ofxLoopinControlNumeric
{
public:
  void bindToShader( ofxLoopinShader * shader ) {
    int value = getValueInt();
    shader->applyUniformInt( key, value );
  };
};

class ofxLoopinUniformVec2 :
  public ofxLoopinUniform,
  public ofxLoopinControlVector<2>
{
public:
  void bindToShader( ofxLoopinShader * shader ) {
    shader->applyUniformVec2( key, getValueVec2() );
  };
};

class ofxLoopinUniformVec3 :
  public ofxLoopinUniform,
  public ofxLoopinControlVector<3>
{
public:
  void bindToShader( ofxLoopinShader * shader ) {
    shader->applyUniformVec3( key, getValueVec3() );
  };
};

class ofxLoopinUniformVec4 :
  public ofxLoopinUniform,
  public ofxLoopinControlVector<4>
{
public:
  void bindToShader( ofxLoopinShader * shader ) {
    shader->applyUniformVec4( key, getValueVec4() );
  };
};
