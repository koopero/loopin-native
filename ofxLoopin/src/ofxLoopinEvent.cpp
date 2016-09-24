#include "ofxLoopinEvent.h"

const string ofxLoopinEvent::Loaded = "loaded";


ofxLoopinEvent ofxLoopinEvent::fileNotFound( const string & file ) {
 ofxLoopinEvent event = ofxLoopinEvent();
 event.type = "notfound";
 event.data["file"] = file;

 return event;
}
