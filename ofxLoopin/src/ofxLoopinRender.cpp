#include "ofxLoopinRender.h"

ofxLoopin::shader::Shader ofxLoopinRender::shaderDefault = ofxLoopin::shader::Shader("shaderDefault") ;

ofxLoopinBuffer * ofxLoopinRender::getBuffer( const string & key, bool create ) {

  assert( root );

  auto has = dynamic_cast<ofxLoopinHasBuffers *> ( root );
  assert( has );
  ofxLoopin::control::Map<ofxLoopinBuffer> * map = has->__getMap();

  return map->getByKey( key, create );
}
