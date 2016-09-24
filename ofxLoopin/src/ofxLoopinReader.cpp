#include "ofxLoopinReader.h"

void ofxLoopinReader::patchString( const string & value ) {
  ofxLoopinControl * target = root->walk( value );
  ofxLoopinEvent event;
  event.type = "read";

  event.path = value;

  if ( event.path == "" )
    event.path = "__root";

  if ( target ) {
    event.data = target->read();
  } else {
    event.data = Json::Value( Json::nullValue );
  }

  dispatch( event );
}
