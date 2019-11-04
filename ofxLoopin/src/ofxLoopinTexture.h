#pragma once

#include "ofxLoopinBuffer.h"
#include "./control/Enum.hpp"
#include "ofxLoopinRef.h"
#include "ofxLoopinRoot.h"
#include "./shader/Shader.hpp"
#include "ofxLoopinUniform.h"

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


class ofxLoopinTexture : public ofxLoopin::control::Control, public ofxLoopinUniform {
public:

  ofxLoopinRef<ofxLoopinBuffer,ofxLoopinHasBuffers> buffer;

  ofxLoopin::control::Enum<GLint,GL_NEAREST> minFilter;
  ofxLoopin::control::Enum<GLint,GL_NEAREST> magFilter;

  ofxLoopin::control::Enum<GLint,GL_REPEAT> wrapH;
  ofxLoopin::control::Enum<GLint,GL_REPEAT> wrapV;


  bool hasTexture() {
    ofxLoopinBuffer * bufferP = buffer.getPointer();
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
    minFilter.setEnumKey( "nearest", GL_NEAREST );
    minFilter.setEnumKey( "linear", GL_LINEAR );
    addSubControl("minFilter", &minFilter );

    magFilter.setEnumKey( "nearest", GL_NEAREST );
    magFilter.setEnumKey( "linear", GL_LINEAR );
    addSubControl("magFilter", &magFilter );

    /** loopin/type/textureWrap:
      type: options
      options:
        - repeat
        - none
        - clamp
    */

    wrapH.setEnumKey("repeat", GL_REPEAT );
    wrapV.setEnumKey("repeat", GL_REPEAT );

    wrapV.setEnumKey("clamp", GL_CLAMP_TO_EDGE );
    wrapH.setEnumKey("clamp", GL_CLAMP_TO_EDGE );

    #ifndef TARGET_OPENGLES
      wrapH.setEnumKey("none", GL_CLAMP_TO_BORDER );
      wrapV.setEnumKey("none", GL_CLAMP_TO_BORDER );
    #endif


    addSubControl("wrapH", &wrapH );
    addSubControl("wrapV", &wrapV );
  };

  int _boundLocation = -1;

};
