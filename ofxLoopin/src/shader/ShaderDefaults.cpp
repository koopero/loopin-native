#include "./ShaderDefaults.hpp"

const string ofxLoopin::shader::ShaderDefaults::GLES_VERT = "\
  precision highp float; \
  uniform mat4 modelViewProjectionMatrix; \
  uniform sampler2D srcSampler; \
  attribute vec4 position; \
  attribute vec2 texcoord; \
  varying vec2 srcCoord; \
  void main() \
  { \
    srcCoord = vec2(texcoord.x, texcoord.y); \
    gl_Position = modelViewProjectionMatrix * position; \
  } \
";


const string ofxLoopin::shader::ShaderDefaults::GLES_FRAG = "\
  precision highp float; \
  uniform sampler2D srcSampler; \
  varying vec2 srcCoord; \
  void main(){ \
    vec4 c = texture2D(srcSampler, srcCoord); \
    gl_FragColor = c; \
  } \
";

const string ofxLoopin::shader::ShaderDefaults::GL_VERT = "\
#version 150\n\
uniform mat4 modelViewProjectionMatrix;\n\
uniform mat4 srcMatrix;\n\
uniform sampler2D srcSampler;\n\
in vec4 position;\n\
in vec2 texcoord;\n\
in vec4 color;\n\
out vec2 srcCoord;\n\
out vec4 vertColour;\n\
void main()\n\
{\n\
    srcCoord = vec2(texcoord.x, texcoord.y);\n\
    vertColour = vec4(1,1,1,1);\n\
    gl_Position = modelViewProjectionMatrix * position;\n\
}\n\
";



const string ofxLoopin::shader::ShaderDefaults::GL_FRAG = "\
  #version 150 \n\
  uniform sampler2D srcSampler; \n\
  in vec2 srcCoord; \n\
  out vec4 outputColour; \n\
  void main() \n\
  { \n\
    vec4 c = texture(srcSampler, srcCoord); \n\
    outputColour = vec4( c.r, c.g, c.b, c.a ); \n\
    // outputColour.r = srcCoord.x; \n\
    // outputColour.g = srcCoord.y; \n\
  } \n\
";
