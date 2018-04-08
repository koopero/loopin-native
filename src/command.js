module.exports = command

const Promise = require( 'bluebird' )
    , spawn = require('child_process').spawn

function command( cmd, args, opt ) {
  const build = this

  opt = opt || {}

  if ( build.verbose ) {
    opt.stdio = opt.stdio || [ 'pipe', process.stdout, process.stderr ]
  }

  return Promise.fromCallback( function ( cb ) {
    const proc = spawn( cmd, args, opt )
    build.log( cmd, args.join(' ') )

    if ( !build.verbose ) {
      proc.stderr && proc.stderr.on('data', (d) => build.warn( String( d ) ) )
      proc.stdout && proc.stdout.on('data', (d) => build.log( String( d ) ) )
    }

    proc.on('close', function ( code ) {
      if ( code ) {
        cb( 'Called utility returned non-zero exit code' )
      } else {
        cb();
      }
    })
  } )
}
