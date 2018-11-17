module.exports = openframeworks

const _ = require('lodash')
    , Promise = require('bluebird')
    , fs = Promise.promisifyAll( require('fs-extra'))
    , glob = Promise.promisify( require('glob') )
    , path = require('path')
    , os = require('os')
    , got = require('got')

function openframeworks( build ) {
  return ensure()

  async function ensure ( ) {
    if ( exists() )
      return

    await ensureZip()
    await unpack()
    await patchOF()

    if ( !exists() )
      throw new Error('Failed to download and unpack openFrameworks')
  }

  function exists() {
    // Random file in the openFrameworks directory
    const file = './CODE_OF_CONDUCT.md'

    return fs.existsSync( build.resolve( build.openframeworks.root, file ) )
  }

  async function ensureZip( ) {
    const version  = build.openframeworks.version
        , zip_name = build.openframeworks.zipName
        , releaseURL = build.openframeworks.releaseURL
        , downloadDir = build.resolve( build.download.dir )
        , dest = build.resolve( downloadDir, zip_name )

    if ( fs.existsSync( dest ) )
      return true

    build.log('mkdir -p', downloadDir )
  
    await fs.ensureDirAsync( downloadDir )

    build.log('cd', downloadDir )
    build.log('wget', releaseURL )

    let data = await got.get( releaseURL, { 
      // This is somewhat dangerous.
      rejectUnauthorized: false,
      encoding: null
    } )

    data = data.body

    await fs.writeFileAsync( dest, data, null )
  }

  async function unpack() {
    const source = build.resolve( build.download.dir, build.openframeworks.zipName )
        , dest = build.resolve( build.openframeworks.root )

    build.log('unzip', source, dest )

    const Decompress = require('decompress')

    await Decompress( source, dest, { strip: 1 } )
  }

  function patchOF() {
    if ( os.platform() != 'linux' )
      return

    build.log('# patching openFrameworks' )
    return Promise.map( [ 'linuxarmv6l','linuxarmv7l' ], function ( arch ) {
      let src  = build.resolve( build['openframeworks']['root'], 'scripts','templates','linux','qtcreator.qbs' )
      let dest = build.resolve( build['openframeworks']['root'], 'scripts','templates', arch,'qtcreator.qbs' )
      build.log('cp', src, dest )
      return fs.copyAsync( src, dest )
    } )
  }
}


