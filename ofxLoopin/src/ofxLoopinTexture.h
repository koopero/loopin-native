#pragma once

#include "ofxLoopinBuffer.h"
#include "ofxLoopinControlEnum.h"
#include "ofxLoopinRef.h"
#include "ofxLoopinRoot.h"
#include "ofxLoopinShader.h"
#include "ofxLoopinUniform.h"

/** loopin/type/texture/sub/:
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


class ofxLoopinTexture : public ofxLoopinControl, public ofxLoopinUniform {
public:

  ofxLoopinRef<ofxLoopinBuffer,ofxLoopinHasBuffers> buffer;

  ofxLoopinControlEnum<GLint,GL_NEAREST> minFilter;
  ofxLoopinControlEnum<GLint,GL_NEAREST> magFilter;

  ofxLoopinControlEnum<GLint,GL_REPEAT> wrapH;
  ofxLoopinControlEnum<GLint,GL_REPEAT> wrapV;


  bool hasTexture() {
    ofxLoopinBuffer * bufferP = buffer.getPointer();
    if ( bufferP ) {
      return bufferP->isAllocated();
    }

    return false;
  }

  void bindToShader( ofxLoopinShader * shader );

  void unbind();


protected:
  void patchString( const string & value ) {
    buffer.patch( value );
  };

  void patchLocal( const Json::Value & value ) {
    if ( value.isObject() ) {
      if ( value.isMember("wrap") ) {
        wrapH.patch( value["wrap"] );
        wrapV.patch( value["wrap"] );
      }

      if ( value.isMember("filter") ) {
        minFilter.patch( value["filter"] );
        magFilter.patch( value["filter"] );
      }
    }
  }

  void addSubControls() {
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
    wrapH.setEnumKey("none", GL_CLAMP_TO_BORDER );
    wrapH.setEnumKey("clamp", GL_CLAMP_TO_EDGE );

    addSubControl("wrapH", &wrapH );

    wrapV.setEnumKey("repeat", GL_REPEAT );
    wrapV.setEnumKey("none", GL_CLAMP_TO_BORDER );
    wrapV.setEnumKey("clamp", GL_CLAMP_TO_EDGE );
    addSubControl("wrapV", &wrapV );
  };

  int _boundLocation = -1;

};
