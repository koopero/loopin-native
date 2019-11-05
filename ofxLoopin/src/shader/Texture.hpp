#pragma once

#include "../base/Buffer.hpp"
#include "./control/Enum.hpp"
#include "./control/Reference.hpp"
#include "../base/Root.hpp"
#include "./shader/Shader.hpp"
#include "./Uniform.hpp"

/** loopin/type/texture/subs/:
  buffer:
    ref: buffer/

  minFilter:
    type: textureFilter

  magFilter:
    type: textureFilter

  wrapH:
    type: textureWrap

  wrapV:
    type: textureWrap
*/

namespace ofxLoopin { namespace shader {
class Texture : public ofxLoopin::control::Control, public Uniform {
public:

  ofxLoopin::control::Reference<ofxLoopin::base::Buffer,ofxLoopin::base::HasBuffers> buffer;

  ofxLoopin::control::Enum<GLint,GL_NEAREST> minFilter;
  ofxLoopin::control::Enum<GLint,GL_NEAREST> magFilter;

  ofxLoopin::control::Enum<GLint,GL_REPEAT> wrapH;
  ofxLoopin::control::Enum<GLint,GL_REPEAT> wrapV;


  bool hasTexture() {
    ofxLoopin::base::Buffer * bufferP = buffer.getPointer();
    if ( bufferP ) {
      return bufferP->isAllocated();
    }

    return false;
  }

  void bindToShader( ofxLoopin::shader::Shader * shader );
  void bindSpecific( ofxLoopin::shader::Shader * shader, string key, int location );
  void unbind();


protected:
  void patchString( string value ) {
    const string bufferName = value; 
    buffer.patch( ofJson( bufferName  ) );
  };

  void patchLocal( const ofJson & value ) {
    if ( value.is_object() ) {
      if ( value.count("wrap") ) {
        wrapH.patch( value["wrap"] );
        wrapV.patch( value["wrap"] );
      }

      if ( value.count("filter") ) {
        minFilter.patch( value["filter"] );
        magFilter.patch( value["filter"] );
      }
    }
  }

  virtual void addSubControls() {
    addSubControl("buffer", &buffer );


    /** loopin/type/textureFilter:
      type: options
      options:
        - linear
        - nearest
    */
    minFilter.enumAddOption( "nearest", GL_NEAREST );
    minFilter.enumAddOption( "linear", GL_LINEAR );
    addSubControl("minFilter", &minFilter );

    magFilter.enumAddOption( "nearest", GL_NEAREST );
    magFilter.enumAddOption( "linear", GL_LINEAR );
    addSubControl("magFilter", &magFilter );

    /** loopin/type/textureWrap:
      type: options
      options:
        - repeat
        - none
        - clamp
    */

    wrapH.enumAddOption("repeat", GL_REPEAT );
    wrapV.enumAddOption("repeat", GL_REPEAT );

    wrapV.enumAddOption("clamp", GL_CLAMP_TO_EDGE );
    wrapH.enumAddOption("clamp", GL_CLAMP_TO_EDGE );

    #ifndef TARGET_OPENGLES
      wrapH.enumAddOption("none", GL_CLAMP_TO_BORDER );
      wrapV.enumAddOption("none", GL_CLAMP_TO_BORDER );
    #endif


    addSubControl("wrapH", &wrapH );
    addSubControl("wrapV", &wrapV );
  };

  int _boundLocation = -1;
};
}};