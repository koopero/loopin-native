#pragma once

#include "./control/Enum.hpp"
#include "../shader/Texture.hpp"

/** loopin/type/show:
  type: texture
*/
namespace ofxLoopin { namespace window {
class Show : public ofxLoopin::shader::Texture {
public:
  enum Alpha {
    IGNOREX,
    MULTIPLY,
    DIVIDE,
    SHOW
  };

  ofxLoopin::control::Enum<Alpha,IGNOREX> alpha;

  // void draw();

  string getBufferDescription() {
    return _bufferDescription;
  };

protected:
  void addSubControls();
  static ofxLoopin::shader::Shader alphaDivideShader;
  static ofxLoopin::shader::Shader alphaShowShader;

};
// end namespace
}};
