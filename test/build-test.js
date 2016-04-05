const build = require('../src/build')
    , util = require('./util')

build( {
  root: util.scratch(''),
  addons: {
    // ofxLoopin: util.root('../ofxLoopin')
  }
})
