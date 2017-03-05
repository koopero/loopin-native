#pragma once

#include "ofxLoopinControl.h"
#include "ofxLoopinFrame.h"
#include "ofxLoopinShaderElement.h"
#include "ofxLoopinFile.h"
#include "ofxLoopinShaderDefaults.h"

#include "ofShader.h"

/** loopin/type/shader
sub:
  vert:
    type: shaderElement

  frag:
    type: shaderElement
*/

class ofxLoopinShader : public ofxLoopinControl {
public:

  ofShader shader;

  ofxLoopinShaderElement vert;
  ofxLoopinShaderElement frag;

  int _textureLocation;

  void begin();
  void end();

  void applyUniformsDefaults() { /* TODO */ };
  void applyUniformsPass( int passIndex, int passTotal );
  void applyUniformsBuffer( ofxLoopinBuffer * buffer );
  void applyUniformsFrame();
  void applyUniformPointSize( float pointSize );
  void applyUniformsGlobalClock();
  
protected:
  void refresh();

  void addSubControls();
};
