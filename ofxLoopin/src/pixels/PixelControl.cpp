#include "./PixelControl.hpp"

void ofxLoopin::pixels::Control::patchLocal( const ofJson & value ) {
  box.patch( value );
  if (
   value.is_object() && (
     value.count("data")
     || value.count("format")
     || value.count("encoding")
     || value.count("channels")
   )
  ) {
    _isDirty = true;
  }

  // Maintain backwards compatibility with 'format'
  if ( value.is_object() && value.count("format") ) {
    encoding.patch( value["format"] );
  }
}

void ofxLoopin::pixels::Control::patchString( string value ) {
  data = value;
  _isDirty = true;
}

void ofxLoopin::pixels::Control::updateLocal( ) {

}

