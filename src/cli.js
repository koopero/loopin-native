#!/usr/bin/env node

const args = require('./parseArgs')()
    , settings = require('./settings')( args )

const treebird = require('treebird')
treebird( settings )

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
//
//
//
