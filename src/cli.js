#!/bin/sh
':' //; exec "$(command -v nodejs || command -v node)" "$0" "$@"

const args = require('./cli/args')
    , Promise = require('bluebird')
    , command = args.command
    , settings = require('./settings')( args )
    , treebird = require('treebird')
    , build = require('./builder')( settings )

var promise = Promise.resolve()
  , runProcess
  , loopin

if ( args.env ) {
  if ( args.dev )
    promise = promise.then( () => require('./build/devEnv')( build ) )

  promise = promise.then( () => {
    const setEnv = ( key, value ) => {
      process.env[key] = value
      console.log( `export ${key}=${value}`)
    }

    setEnv( 'LOOPIN_NATIVE_ROOT', build.root )
    setEnv( 'LOOPIN_NATIVE_DEV', build.dev ? '1' : '' )

    process.exit()
  })
}

if ( args.zip ) {
  promise = promise.then( () => require('./build/zip')( build ) )
}

if ( args.info ) {
  promise = promise.then( () => run() )
  promise = promise.then( () =>
    runLoopin()
    .then( () => loopin.read( 'info/' ) )
    .then( outputResult )
    .then( quit )
  )
}

if ( args.run ) {
  promise = promise.then( () => run() )
  promise = promise.then( () => pipeStdio() )
}

function run() {
  return require('./build/run')( build )
  .then( ( build_process ) => {
    runProcess = build_process
  } )
}

function pipeStdio() {
  runProcess.stdout.pipe( process.stdout )
  runProcess.stderr.pipe( process.stderr )
  process.stdin.pipe( runProcess.stdin )
}

function runLoopin() {
  loopin = require('loopin')()
  loopin.plugin( 'read' )
  loopin.plugin( require('./plugin'), {
    process: runProcess
  })

  return loopin.bootstrap()
}

function outputResult( result ) {
  if ( args.json ) {
    process.stdout.write( JSON.stringify( result, null, 2 ) )
  } else {
    treebird( result )
  }
}

function quit() {
  if ( loopin )
    loopin.close()

  process.exit()
}

// if ( args.run || args.test ) {
//   promise = promise.then( () => require('./build/run')( build ) )
//
//   promise = promise.then( ( build_process ) => {
//     runProcess = build_process
//
//     if ( !args.test ) {
//
//     }
//
//     process.on('exit', function () {
//       if ( _process )
//         runProcess.kill()
//     })
//   })
//   promise = promise.then( () => {
//     if ( args.test ) {
//       runProcess.stdin.write('{"text":{"test":"Loopin Lives!"},"show":"test"}\n')
//       runProcess.stdin.write('{"read":"info"}\n')
//     }
//   })
// } else {
//   promise = promise.then( ( result ) => treebird( build ) )
// }
