#pragma once

#include "./Control.hpp"
#include "../base/File.hpp"

namespace ofxLoopin { namespace control {
class Filename : public Control {
public:
  Filename() {};
  string operator()() const { return _filename; };
  operator string() const { return _filename; };

  string fileAbsolute() const { return base::File::find(_filename); }; 

  bool hasChanged() {
    if ( _hasChanged ) {
      _hasChanged = false;
      return true;
    }

    return false;
  }

protected:
  void patchString( string value ) override {
    if ( value != _filename ) {
      _filename = value;
      _hasChanged = true;
    }
  };
  void readLocal( ofJson & value ) override {
    value = _filename;
  };


private:
  string _filename;
  bool _hasChanged;
};
}};