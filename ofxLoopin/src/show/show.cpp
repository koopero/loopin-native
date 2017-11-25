#include "./show.hpp"

ofxLoopinShader ofxLoopin::Show::alphaDivideShader = ofxLoopinShader(
#ifndef TARGET_OPENGLES
// name
"alphaDivide",
// frag
"#version 150 \n\
uniform sampler2D srcSampler; \n\
in vec2 srcCoord; \n\
out vec4 OUT; \n\
void main() \n\
{ \n\
  OUT = texture(srcSampler, srcCoord); \n\
  OUT.rgb /= OUT.a; \n\
  // OUT.r  = 1.0 - OUT.r; \n\
  // OUT.a   = 1.0; \n\
} \n\
"
#else
#warning "Alpha divide on OpenGL ES not supported"
#endif
);

void ofxLoopin::Show::addSubControls() {
  ofxLoopinTexture::addSubControls();
  wrapV.setEnumValue(GL_CLAMP_TO_EDGE );
  wrapH.setEnumValue(GL_CLAMP_TO_EDGE );

  alpha.setEnumKey("ignore", IGNORE );
  alpha.setEnumKey("multiply", MULTIPLY );
  alpha.setEnumKey("divide", DIVIDE );

  addSubControl("alpha", &alpha );
}


void ofxLoopin::Show::draw() {
  stringstream description;

  description << buffer.key;

  if ( !hasTexture() ) {
    description << " NOT RENDERED";
    _bufferDescription = description.str();
    return;
  }

  ofRectangle area = ofRectangle( 0, 0, ofGetWindowWidth(), ofGetWindowHeight() );

  ofxLoopinBuffer * bufferP = buffer.getPointer();
  ofTexture * texture = bufferP->getTexture();

  if ( !texture || !texture->isAllocated() ) {
    description << " NOT ALLOCATED?!!";
    _bufferDescription = description.str();

    return;
  }


  description << " ( " << texture->getWidth() << "x" << texture->getHeight();
  description << " " << bufferP->format.getKey();
  description << " )";
  _bufferDescription = description.str();
  texture->setTextureWrap( wrapH.getEnumValue(), wrapV.getEnumValue() );
  texture->setTextureMinMagFilter( minFilter.getEnumValue(), magFilter.getEnumValue() );

  switch( alpha.getEnumValue() ) {
    case IGNORE:
      ofDisableBlendMode();
      texture->draw( area );
    break;

    case MULTIPLY:
      ofClear( 0, 0, 0, 0 );
      ofEnableBlendMode( OF_BLENDMODE_ALPHA );
      texture->draw( area );
    break;

    case DIVIDE:
      ofDisableBlendMode();
      alphaDivideShader.begin();
      bindSpecific( &alphaDivideShader, "src", 0 );
      texture->draw( area );
      alphaDivideShader.end();
    break;
  }

}
