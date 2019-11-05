#include "../render/Render.hpp"

ofxLoopin::shader::Shader ofxLoopin::render::Render::shaderDefault = ofxLoopin::shader::Shader("shaderDefault") ;

ofxLoopin::base::Buffer * ofxLoopin::render::Render::getBuffer( const string & key, bool create ) {

  assert( root );

  auto has = dynamic_cast<ofxLoopin::base::HasBuffers *> ( root );
  assert( has );
  ofxLoopin::control::Map<ofxLoopin::base::Buffer> * map = has->__getMap();

  return map->getByKey( key, create );
}
