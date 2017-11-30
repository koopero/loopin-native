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
} else if ( args.info ) {
  promise = promise.then( () => run() )
  promise = promise.then( () =>
    runLoopin()
    .then( () => loopin.read( 'info/' ) )
    .then( outputResult )
    .then( quit )
  )
} else if ( args.test ) {
  promise = promise.then( () =>
    runLoopin()
    .then( () => loopin.patch( {"text":{"test":"Loopin Lives!"},"show":"test"} ))
  )
} else if ( args.run ) {
  promise = promise.then( () => run() )
  promise = promise.then( () => pipeStdio() )
} else {
  promise = promise.then( () => require('./build/executable')( build ) )
  promise = promise.then( () => build )
  promise = promise.then( outputResult )


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
