/**
  Get the current openframeworks platform.

  Possible values:
    osx
*/

const os = require('os')
    , _ = require('lodash')

const NOT_SUPPORTED = [ 'win32', 'freebsd', 'sunos' ]

const os_platform = os.platform()

if ( NOT_SUPPORTED.indexOf( os_platform ) != -1 )
  throw new Error( 'Your platform is not supported at this time.' )

if ( os.platform() == 'darwin') {
  module.exports = 'osx'
  return
}

// Linux at this point, but what architecture?
const architecture = _.trim( command( 'uname -m' ) )

switch( architecture ) {
  case 'x86_64':
    module.exports = 'linux64'
    return

  case 'armv7l':
    // ! Bad hack !
    // Substituting architectures here!!
    module.exports = 'linuxarmv6l'

  default:
    throw new Error( 'Your architecture is not supported at this time.' )
}

function command( cmd ) {
  return require('child_process').execSync( cmd, { encoding: 'ascii' } )
}
