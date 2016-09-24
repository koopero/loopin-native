#pragma once

#include "ofxLoopinControl.h"
#include "ofxLoopinFrame.h"
#include "ofxLoopinShaderElement.h"
#include "ofxLoopinFile.h"

#include "ofShader.h"

class ofxLoopinShader : public ofxLoopinControl {
public:

  ofShader shader;

  ofxLoopinShaderElement vert;
  ofxLoopinShaderElement frag;

  int _textureLocation;

  void begin();
  void end();

  void applyUniformsDefaults() { /* TODO */ };
  void applyUniformsPass( int passIndex, int passTotal ) {
    shader.setUniform1i( "passIndex", passIndex );
    shader.setUniform1i( "passTotal", passTotal );
    shader.setUniform1f( "passDensity", 1.0 / (float) passTotal );
    shader.setUniform1f( "passX", (float) passIndex / (float) passTotal );
  };

  void applyUniformsBuffer( ofxLoopinBuffer * buffer ) {
    shader.setUniform1f( "bufferAspect", buffer->getAspect() );

  }

  void applyUniformsFrame() {
    ofxLoopinFrame frame = root->frame;
    shader.setUniform1i( "clockIndex", frame.index );
    shader.setUniform1f( "clockTime", frame.time );
    shader.setUniform1f( "clockDelta", frame.delta );
  }

  void applyUniformPointSize( float pointSize ) {
    shader.setUniform1f( "pointSize", pointSize );
    shader.setUniform1f( "pointDensity", 1.0 / pointSize / pointSize );
  }


protected:
  void refresh();

  void addSubControls() {

    string fragDefaultFile = ofxLoopinFile::find( "shader/"+key+".frag" );
    string vertDefaultFile = ofxLoopinFile::find( "shader/"+key+".vert" );

    if ( vertDefaultFile.size() ) {
      vert.file = vertDefaultFile;
    } else {
      vert.data =
        "#version 150\n"
        "uniform mat4 modelViewProjectionMatrix;\n"
        "uniform mat4 srcMatrix;\n"
        "uniform sampler2D srcSampler;\n"
        "in vec4 position;\n"
        "in vec2 texcoord;\n"
        "out vec2 srcCoord;\n"
        "void main()\n"
        "{\n"
        "    srcCoord = vec2(texcoord.x, texcoord.y);\n"
        "    srcCoord = (srcMatrix*vec4(srcCoord.x,srcCoord.y,0,1)).xy;\n"
        // "    srcCoord *= textureSize( srcSampler );\n"
        "    gl_Position = modelViewProjectionMatrix * position;\n"
        "}\n";
    }
    vert.dataIsNew = true;

    if ( fragDefaultFile.size() ) {
      frag.file = fragDefaultFile;
    } else {
      frag.data =
        "#version 150\n"
        "uniform sampler2D srcSampler;\n"
        "in vec2 srcCoord;\n"
        "out vec4 outputColour;\n"
        "void main()\n"
        "{\n"
        "  vec4 c = texture(srcSampler, srcCoord);\n"
        "  outputColour = vec4( c.r, c.g, c.b, c.a );\n"
        "}\n";
    }
    frag.dataIsNew = true;

    addSubControl("vert", &vert );
    addSubControl("frag", &frag );
  };
};
