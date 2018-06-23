#include "ofxLoopinControl.h"
#include "ofxLoopinRoot.h"

void ofxLoopinControl::update() {
  for ( auto it = subs.begin(); it != subs.end(); it ++ ) {
    ofxLoopinControl * sub = it->second;
    sub->update();
  }

  for ( auto & unkeyed : subsUnkeyed ) {
    unkeyed->update();
  }

  updateLocal();
};


ofJson ofxLoopinControl::read() {
  ofJson value = ofJson();
  readToValue( value );
  return value;
};

void ofxLoopinControl::readToValue( ofJson & value ) {
  if ( value.is_object () ) {
    readSubs( value );
  }

  readLocal( value );

}

void ofxLoopinControl::readSubs( ofJson & value ) {
  for ( auto it = subs.begin(); it != subs.end(); it ++ ) {
    const string & key = it->first;
    ofxLoopinControl * sub = it->second;

    value[ key ] = sub->read();
  }

  for ( auto & unkeyed : subsUnkeyed ) {
    unkeyed->readToValue( value );
  }
};

void ofxLoopinControl::patch ( const ofJson & val ) {
  //  std::cerr << "patch" << val << endl;

  patchLocal( val );

  if ( val.is_string() ) {
    patchString( val.get<std::string>() );
  }

  for ( auto & unkeyed : subsUnkeyed ) {
    unkeyed->patch( val );
  }

  if ( val.is_object() && !val.empty() && !val.is_array() ) {
    typedef map<string, ofxLoopinControl *>::iterator it_type;

    for ( it_type it = subs.begin(); it != subs.end(); it ++ ) {
      string key = it->first;

      // cout << "set " << key << endl;
      if ( val.count( key ) ) {
        ofxLoopinControl * sub = it->second;
        sub->patch( val[ key ] );
      }
    }

    for( auto it = val.begin(); it != val.end() ; it++) {
      patchKey( it.key(), *it );
    }
  }

  patchLocalAfter( val );

}

void ofxLoopinControl::dispatch( ofxLoopinEvent & event ) {
  if ( root ) {
    if ( !event.path.size() )
      event.path = path;

    if ( event.path == "__root" )
      event.path = "";

    root->dispatch( event );
  } else {
    std::cerr << " no root " << path << endl;
  }
}


void ofxLoopinControl::addSubControl( ofxLoopinControl * control ) {
  addSubControl( "", control );
}

void ofxLoopinControl::addSubControl( string key, ofxLoopinControl * control ) {
  control->path = path.size() && key.size() ? path + "/" + key : path.size() ? path : key ;
  control->key = key;
  control->root = root;
  control->setupControl();

  // cout << "addSUb " << key << " " << control->path << endl;

  if ( key.size() ) {
    subs[key] = control;
  } else {
    subsUnkeyed.push_back( control );
  }
}

ofxLoopinControl * ofxLoopinControl::walk( const string & path ) {
  if ( !path.size() )
    return this;

  size_t delim = path.find_first_of( "./");
  string key, remain;
  if ( delim == string::npos ) {
    key = path;
  } else {
    key = path.substr( 0, delim );
    remain = path.substr( delim + 1 );
  }

  if ( key.size() && subs.count( key ) ) {
    return subs[key]->walk( remain );
  }

  if ( !key.size() && remain.size() )
    return walk( remain );

  if ( !key.size() && !remain.size() )
    return this;

  return NULL;
}
