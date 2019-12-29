#pragma once

#include "./Data.hpp"
#include "../control/Control.hpp"
#include "../control/Enum.hpp"
#include "../control/Value.hpp"


namespace ofxLoopin { namespace pixels {
class Control : virtual public ofxLoopin::control::Control, public Data {
public:

protected:
  void updateLocal();
  void patchLocal( const ofJson & value );
  void patchString( string value );
  void dispatchData();
  void addSubControls() {
    addPixelDataSubControls();
  };
  void addPixelDataSubControls() {
    encoding.enumAddOption( "hex", ENCODING_HEX );
    encoding.enumAddOption( "hex2", ENCODING_HEX2 );
    encoding.enumAddOption( "float", ENCODING_FLOAT );
    encoding.enumAddOption( "percent", ENCODING_PERCENT );
    encoding.enumAddOption( "decimal", ENCODING_DECIMAL );
    encoding.enumAddOption( "base64", ENCODING_BASE64 );
    addSubControl("encoding", &encoding );
    addSubControl("channels", new ofxLoopin::control::Value( &channels ) );
    addSubControl("data", new ofxLoopin::control::Value( &data ) );
  }
};
// end of namespace
}}
