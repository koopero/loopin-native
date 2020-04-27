#include "./Event.hpp"

const string ofxLoopin::control::Event::Loaded = "loaded";

ofxLoopin::control::Event ofxLoopin::control::Event::fileNotFound( const string & file ) {
 ofxLoopin::control::Event event = ofxLoopin::control::Event();
 event.type = "error";
 event.data["file"] = file;
 event.data["error"] = "File not found";

 return event;
}
