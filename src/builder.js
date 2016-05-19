module.exports = builder


const settings = require('./settings')

const _ = require('lodash')
    , Promise = require('bluebird')
    , boptions = require('boptions')
    , fs = Promise.promisifyAll( require('fs-extra'))
    , glob = Promise.promisify( require('glob') )
    , path = require('path')
    , os = require('os')
    , Download = require('download')
    , downloadStatus = require('download-status')

builder.options = require('boptions')({
  'quiet': true,
  'verbose': false,
  'run': false,
  'root': {
    '#default': path.resolve( __dirname, '../build' )
  },
  'openframeworks': {
    '#default': process.env['OF_ROOT']
  },
  'addons': {}
})

function builder( opt ) {
  const build = Object.create( builder.prototype )
  _.extend( build, builder.options( arguments ) )

  build.settings = settings
  build.platform = require('./platform')
  build.addons = _.merge( _.clone( settings['addons'] ), opt.addons )
  build.resolve = function () {
    return path.resolve.apply( path, _.concat( [build.root], arguments ) )
  }
  build.command = require('./command').bind( build )

  build.log = function ( line ) {
    if ( build.quiet )
      return

    if ( _.isString( line ) )
      while ( line != ( line = line.replace( build.root, '.' ) ) ) {}

    console.log.apply( console, arguments )
  }

  build.warn = function ( line ) {
    if ( build.quiet || !build.verbose ) {
      build.stderr = ( build.stderr || '' ) + line
      return
    }

    if ( _.isString( line ) )
      while ( line != ( line = line.replace( build.root, '.' ) ) ) {}

    console.error.apply( console, arguments )
  }

  build.error = function ( line ) {
    if ( build.quiet ) {
      build.stderr = ( build.stderr || '' ) + line
      return
    }

    console.error.apply( console, arguments )
  }

  build.substitute = function( str ) {
    return str.replace( /{([\w\.]+)}/g, ( match, key ) =>
      _.get( build, _.trim( key ) )
      || _.get( build.settings, _.trim( key ) )
      || ''
    )
  }

  var promise = Promise.resolve()
    .then( require('./openframeworks').bind( build ) )
    .then( require('./addons').bind( build ) )
    .then( require('./project').bind( build ) )
    .then( require('./make').bind( build ) )
    .catch( function ( e ) {
      console.error( build.stderr || '' )
      throw e
    })

  if ( build.run )
    promise = promise.then( require('./run').bind( build, opt ) )

  promise = promise
    .then( () => build )

  return promise
}
