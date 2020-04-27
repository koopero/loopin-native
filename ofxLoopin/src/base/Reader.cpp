#include "./Reader.hpp"

void ofxLoopin::base::Reader::patchString( string value ) {
  ofxLoopin::control::Control * target = root->walk( value );
  ofxLoopin::control::Event event;
  event.type = "read";

  event.path = value;

  if ( event.path == "" )
    event.path = "__root";

  if ( target ) {
    event.data = target->read();
  } else {
    event.data = ofJson();
  }

  dispatch( event );
}
