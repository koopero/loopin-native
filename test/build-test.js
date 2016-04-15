const builder = require('../src/builder')
    , util = require('./util')

builder( {
  root: util.scratch(''),
  quiet: false,
  verbose: 1,
  run: true,
  addons: {
    ofxLoopin: util.root('../ofxLoopin')
  }
})
  .then( function ( build ) {
  })
