module.exports = { defaultPlatform, validatePlatform }

const os = require('os')
    , _ = require('lodash')

function defaultPlatform( settings ) {
  let platform = os.platform()

  if ( platform == 'darwin' ) {
    platform = 'osx'
  } else if ( platform == 'linux' ) {
    platform += defaultArchitecture()
  }

  return platform
}

function validatePlatform( platform ) {
  switch ( platform ) {
    case 'linux64':
    case 'linuxarmv6l':
      if ( os.platform() != 'linux' )
        throw new Error( `Cross-compilation not supported.` )
    break

    case 'osx':
      if ( os.platform() != 'darwin' )
        throw new Error( `Cross-compilation not supported.` )
    break

    case 'win32':
      if ( os.platform() != 'win32' )
        throw new Error( `Cross-compilation not supported.` )
    break

    default:
      throw new Error( `Platform ${platform} is not supported at this time.` )
  }
}


function defaultArchitecture() {
  let arch = _.trim( command( 'uname -m' ) )
  switch ( arch ) {
    case 'x86_64':
      arch = '64'
    break

    case 'armv6l':
    case 'armv7l':
    case 'arm':
    case 'arm64':
      // ! Bad hack !
      // Substituting architectures here!!
      arch = 'armv6l'
    break
  }
  return arch
}

function command( cmd ) {
  return require('child_process').execSync( cmd, { encoding: 'ascii' } )
}
