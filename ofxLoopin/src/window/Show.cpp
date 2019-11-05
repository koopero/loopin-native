#include "./Show.hpp"

ofxLoopin::shader::Shader ofxLoopin::window::Show::alphaDivideShader = ofxLoopin::shader::Shader(
// name
"alphaDivide",
#ifndef TARGET_OPENGLES
// frag
"#version 150 \n\
uniform sampler2D srcSampler; \n\
in vec2 srcCoord; \n\
out vec4 OUT; \n\
void main() \n\
{ \n\
  OUT = texture(srcSampler, srcCoord); \n\
  OUT.rgb /= OUT.a; \n\
} \n\
"
#else
"precision highp float; \n\
uniform sampler2D srcSampler; \n\
varying vec2 srcCoord; \n\
void main(){ \n\
  gl_FragColor = texture2D(srcSampler, srcCoord); \n\
  gl_FragColor.rgb /= gl_FragColor.a; \n\
} \n\
"
#endif
);

ofxLoopin::shader::Shader ofxLoopin::window::Show::alphaShowShader = ofxLoopin::shader::Shader(
// name
"alphaShow",
#ifndef TARGET_OPENGLES

// frag
"#version 150 \n\
uniform sampler2D srcSampler; \n\
in vec2 srcCoord; \n\
out vec4 OUT; \n\
void main() \n\
{ \n\
  OUT = texture(srcSampler, srcCoord); \n\
  OUT.r = OUT.a; \n\
  OUT.g = OUT.a; \n\
  OUT.b = OUT.a; \n\
  OUT.a = 1.0; \n\
} \n\
"
#else
"precision highp float; \n\
uniform sampler2D srcSampler; \n\
varying vec2 srcCoord; \n\
void main(){ \n\
  vec4 c = texture2D(srcSampler, srcCoord); \n\
  gl_FragColor.r = c.a; \n\
  gl_FragColor.g = c.a; \n\
  gl_FragColor.b = c.a; \n\
  gl_FragColor.a = c.a; \n\
} \n\
"
#endif
);

void ofxLoopin::window::Show::addSubControls() {
  ofxLoopin::shader::Texture::addSubControls();
  wrapV.setEnumValue(GL_CLAMP_TO_EDGE );
  wrapH.setEnumValue(GL_CLAMP_TO_EDGE );

  alpha.enumAddOption("ignore", IGNOREX );
  alpha.enumAddOption("multiply", MULTIPLY );
  alpha.enumAddOption("divide", DIVIDE );
  alpha.enumAddOption("show", SHOW );

  addSubControl("alpha", &alpha );
}


void ofxLoopin::window::Show::draw() {
  stringstream description;

  description << buffer.key;

  if ( !hasTexture() ) {
    description << " NOT RENDERED";
    _bufferDescription = description.str();
    return;
  }

  ofRectangle area = ofRectangle( 0, 0, ofGetWindowWidth(), ofGetWindowHeight() );

  ofxLoopin::base::Buffer * bufferP = buffer.getPointer();
  ofTexture * texture = bufferP->getTexture();

  if ( !texture || !texture->isAllocated() ) {
    description << " NOT ALLOCATED?!!";
    _bufferDescription = description.str();

    return;
  }


  description << " ( " << texture->getWidth() << "x" << texture->getHeight();
  description << " " << bufferP->format.getKey();
  description << " alpha: " << alpha.getKey();
  description << " )";
  _bufferDescription = description.str();
  texture->setTextureWrap( wrapH.getEnumValue(), wrapV.getEnumValue() );
  texture->setTextureMinMagFilter( minFilter.getEnumValue(), magFilter.getEnumValue() );

  switch( alpha.getEnumValue() ) {
    case IGNOREX:
      ofEnableBlendMode( OF_BLENDMODE_DISABLED );
      texture->draw( area );
    break;

    case MULTIPLY:
      ofClear( 0, 0, 0, 0 );
      ofEnableBlendMode( OF_BLENDMODE_ALPHA );
      texture->draw( area );
    break;

    case DIVIDE:
      ofEnableBlendMode( OF_BLENDMODE_DISABLED );
      alphaDivideShader.begin();
      bindSpecific( &alphaDivideShader, "src", 0 );
      texture->draw( area );
      alphaDivideShader.end();
    break;

    case SHOW:
      ofEnableBlendMode( OF_BLENDMODE_DISABLED );
      alphaShowShader.begin();
      bindSpecific( &alphaShowShader, "src", 0 );
      texture->draw( area );
      alphaShowShader.end();
    break;
  }

}
