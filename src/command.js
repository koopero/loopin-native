module.exports = command

const Promise = require( 'bluebird' )
    , spawn = require('child_process').spawn

function command( cmd, args, opt ) {
  const build = this

  opt = opt || {}

  return Promise.fromCallback( function ( cb ) {
    const process = spawn( cmd, args, opt )
    build.log( cmd, args.join(' ') )

    process.stderr.on('data', (d) => build.warn( String( d ) ) )

    if ( build.verbose )
      process.stdout.on('data', (d) => build.log( String( d ) ) )

    process.on('close', function ( code ) {
      if ( code ) {
        cb( 'non zero code' )
      } else {
        cb();
      }
    })
  } )
}
