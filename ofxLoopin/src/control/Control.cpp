#include "./Control.hpp"
#include "../base/Root.hpp"

void ofxLoopin::control::Control::update() {
  for ( auto it = subs.begin(); it != subs.end(); it ++ ) {
    ofxLoopin::control::Control * sub = it->second;
    sub->update();
  }

  for ( auto & unkeyed : subsUnkeyed ) {
    unkeyed->update();
  }

  updateLocal();
};


ofJson ofxLoopin::control::Control::read() {
  ofJson value = ofJson::object();
  readToValue( value );
  return value;
};

void ofxLoopin::control::Control::readToValue( ofJson & value ) {
  if ( value.is_object () ) {
    readSubs( value );
  }

  readLocal( value );

}

void ofxLoopin::control::Control::readSubs( ofJson & value ) {
  for ( auto it = subs.begin(); it != subs.end(); it ++ ) {
    const string & key = it->first;
    ofxLoopin::control::Control * sub = it->second;

    value[ key ] = sub->read();
  }

  for ( auto & unkeyed : subsUnkeyed ) {
    unkeyed->readToValue( value );
  }
};

void ofxLoopin::control::Control::patch ( const ofJson & val ) {
  patchLocal( val );

  if ( val.is_string() ) {
    patchString( val.get<std::string>() );
  }

  for ( auto & unkeyed : subsUnkeyed ) {
    unkeyed->patch( val );
  }

  if ( val.is_object() && !val.empty() && !val.is_array() ) {
    typedef map<string, ofxLoopin::control::Control *>::iterator it_type;

    for ( it_type it = aliases.begin(); it != aliases.end(); it ++ ) {
      string key = it->first;

      if ( val.count( key ) ) {
        ofxLoopin::control::Control * sub = it->second;
        sub->patch( val[ key ] );
      }
    }

    for ( it_type it = subs.begin(); it != subs.end(); it ++ ) {
      string key = it->first;

      if ( val.count( key ) ) {
        ofxLoopin::control::Control * sub = it->second;
        sub->patch( val[ key ] );
      }
    }

    for( auto it = val.begin(); it != val.end() ; it++) {
      patchKey( it.key(), *it );
    }
  }

  patchLocalAfter( val );

}

void ofxLoopin::control::Control::patchKey( string key, const ofJson & val ) {
  
}

void ofxLoopin::control::Control::dispatch( ofxLoopin::control::Event & event ) {
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


void ofxLoopin::control::Control::addSubControl( ofxLoopin::control::Control * control ) {
  addSubControl( "", control );
}

void ofxLoopin::control::Control::addSubControl( string key, ofxLoopin::control::Control * control ) {
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

void ofxLoopin::control::Control::addSubControlAlias( string key, ofxLoopin::control::Control * control ) {
  aliases[key] = control;
}



ofxLoopin::control::Control * ofxLoopin::control::Control::walk( const string & path ) {
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
