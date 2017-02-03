#include "ofxLoopinEvent.h"

const string ofxLoopinEvent::Loaded = "loaded";


ofxLoopinEvent ofxLoopinEvent::fileNotFound( const string & file ) {
 ofxLoopinEvent event = ofxLoopinEvent();
 event.type = "error";
 event.data["file"] = file;
 event.data["error"] = "File not found";

 return event;
}
