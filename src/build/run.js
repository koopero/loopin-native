module.exports = run

const _ = require('lodash')
    , os = require('os')
    , spawn = require('child_process').spawn

function run( build ) {
  return require( './executable')( build )
  .then( function ( execPath ) {
    const env = _.clone( process.env )

    // Try to connect to main screen on linux systems
    if ( os.platform() == 'linux' && !env['DISPLAY'] )
      env['DISPLAY'] = ':0'

    build.log( execPath )
    const proc = spawn( execPath, [], { cwd: build.resolve(), env: env } )
    return proc
  })
}
