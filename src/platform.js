/**
  Get the current openframeworks platform.

  Possible values:
    osx
*/

const os = require('os')

const NOT_SUPPORTED = [ 'win32', 'freebsd', 'sunos' ]

const os_platform = os.platform()

if ( NOT_SUPPORTED.indexOf( os_platform ) != -1 )
  throw new Error( 'Your platform is not supported at this time.' )

if ( os.platform() == 'darwin') {
  module.exports = 'osx'
  return
}

// Linux at this point, but what architecture?
const command = require('./command')
const architecture = command( 'uname -m' )

// TODO
