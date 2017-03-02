#include "ofxLoopinShaderDefaults.h"

#define MULTI_LINE_STRING(a) #a


const string ofxLoopinShaderDefaults::GLES_VERT = "\
  precision highp float; \
  uniform mat4 modelViewProjectionMatrix; \
  uniform mat4 srcMatrix; \
  uniform sampler2D srcSampler; \
  attribute vec4 position; \
  attribute vec2 texcoord; \
  varying vec2 srcCoord; \
  void main() \
  { \
    srcCoord = vec2(texcoord.x, texcoord.y); \
    srcCoord = (srcMatrix*vec4(srcCoord.x,srcCoord.y,0,1)).xy; \
    gl_Position = modelViewProjectionMatrix * position; \
  } \
";


const string ofxLoopinShaderDefaults::GLES_FRAG = "\
  precision highp float; \
  uniform sampler2D srcSampler; \
  varying vec2 srcCoord; \
  void main(){ \
    vec4 c = texture2D(srcSampler, srcCoord); \
    gl_FragColor = c; \
  } \
";

const string ofxLoopinShaderDefaults::GL_VERT = "\
  #version 150 \n\
  uniform mat4 modelViewProjectionMatrix; \
  varying vec4 position; \
  varying vec2 texcoord; \
  varying vec2 srcCoord; \
  void main() \
  { \
      gl_Position = modelViewProjectionMatrix * position; \
  } \
";



const string ofxLoopinShaderDefaults::GL_FRAG = "\
  #version 150 \n\
  uniform sampler2D srcSampler; \
  in vec2 srcCoord; \
  out vec4 outputColour; \
  void main() \
  { \
    vec4 c = texture(srcSampler, srcCoord); \
    outputColour = vec4( c.r, c.g, c.b, c.a ); \
  } \
";
