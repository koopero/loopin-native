module.exports = run

const _ = require('lodash')
    , os = require('os')
    , spawn = require('child_process').spawn

function run( build, stdio ) {
  return require( './executable')( build )
  .then( function ( execPath ) {
    const env = _.clone( process.env )

    // Try to connect to main screen on linux systems
    if ( os.platform() == 'linux' && !env['DISPLAY'] )
      env['DISPLAY'] = ':0'

    build.log( execPath )
    const opt = {
      cwd: build.cwd,
      env: env,
      stdio: stdio || 'pipe'
    }
    const proc = spawn( execPath, [], opt )
    return proc
  })
}
