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

promise = promise.then( () => require('./build/executable')( build ) )

if ( args.zip ) {
  promise = promise.then( () => require('./build/zip')( build ) )
}

if ( args.run && !args.which ) {
  promise = promise.then( () => require('./build/run')( build ) )
  promise = promise.then( ( build_process ) => {
    runProcess = build_process
    runProcess.stdout.pipe( process.stdout )
    runProcess.stderr.pipe( process.stderr )
    process.stdin.pipe( runProcess.stdin )

    process.on('exit', function () {
      if ( _process )
        runProcess.kill()
    })
  })
  promise = promise.then( () => {
    if ( args.test ) {
      runProcess.stdin.write('{"text":{"test":"Loopin Lives!"},"show":"test"}\n')
      runProcess.stdin.write('{"read":"info"}\n')
    }
  })
} else {
  promise = promise.then( ( result ) => treebird( build ) )
}
