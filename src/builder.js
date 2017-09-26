module.exports = builder


const settings = require('./settings')

const _ = require('lodash')
    , Promise = require('bluebird')
    , fs = Promise.promisifyAll( require('fs-extra'))
    , glob = Promise.promisify( require('glob') )
    , path = require('path')



function builder( settings ) {
  const build = Object.create( builder.prototype )
  _.extend( build, settings )

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

  build.checkFile = function () {
    let file = this.resolve.apply( this, arguments )
    return fs.existsSync( file )
  }

  return build
}
