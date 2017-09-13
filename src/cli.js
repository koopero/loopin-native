#!/bin/sh
':' //; exec "$(command -v nodejs || command -v node)" "$0" "$@"

const args = require('./cli/args')
    , Promise = require('bluebird')
    , command = args.command
    , settings = require('./settings')( args )
    , treebird = require('treebird')
    , build = require('./builder')( settings )

var promise = Promise.resolve()

promise = promise.then( () => require('./build/executable')( build ) )

if ( args.zip ) {
  promise = promise.then( () => require('./build/zip')( build ) )
}

promise = promise.then( () => require('./build/run')( build ) )
promise = promise.then( ( result ) => treebird( build ) )

// const native = require('./builder')
//     , yaml = require('js-yaml')
//     ,
//     , pkg = require('../package.json')

//
// addArgparseArguments( parser )
//
//
// const opt =
//
// var presets = require('./presets')( opt.preset )
// var presetData = presets.load()
//
// if ( opt.test ) {
//   presetData += '{"text":{"test":"Loopin Lives!"},"show":"test"}\n'
//   presetData += '{"read":"info"}\n'
// }
//
// var _process
//
// native( opt )
// .then( function ( build ) {
//   _process = build.process
//
//   const write = ( str ) => _process && _process.stdin.write( str )
//   write( presetData )
//
//   console.log(presetData)
//
//   if ( opt.watch )
//     presets.watch( write )
//
//   if ( _process ) {
//
//     _process.stdout.pipe( process.stdout )
//     _process.stderr.pipe( process.stderr )
//     process.stdin.pipe( _process.stdin )
//
//     _process.on('exit', function () {
//       process.exit()
//     })
//   }
// } )
//
// process.on('exit', function () {
//   if ( _process )
//     _process.kill()
// })
