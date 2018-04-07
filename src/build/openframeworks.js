module.exports = openframeworks

const _ = require('lodash')
    , Promise = require('bluebird')
    , fs = Promise.promisifyAll( require('fs-extra'))
    , glob = Promise.promisify( require('glob') )
    , path = require('path')
    , os = require('os')
    , Download = require('download')
    , downloadStatus = require('download-status')


function openframeworks( build ) {
  return ensure()

  function ensure ( ) {
    if ( exists() )
      return

    return ensureZip()
      .then( unpack )
      .then( patchOF )
  }

  function exists() {

    // Random file in the openFrameworks directory
    const file = './CODE_OF_CONDUCT.md'

    return fs.existsSync( build.resolve( build.openframeworks.root, file ) )
  }

  function ensureZip( ) {
    const version  = build.openframeworks.version
        , zip_name = build.openframeworks.zipName
        , release_url = build.openframeworks.releaseURL
        , downloadDir = build.resolve( build.download.dir )

    if ( fs.existsSync( build.resolve( downloadDir, zip_name ) ) )
      return Promise.resolve( true )


    build.log('cd', downloadDir )
    build.log('wget', release_url )

    var download = new Download({strip: 1})
        .get( release_url, downloadDir )

    if ( !build.quiet )
        download = download.use(downloadStatus())

    return Promise.fromCallback( ( callback ) => download.run( callback ) )
  }

  function unpack() {
    const source = build.resolve( build.download.dir, build.openframeworks.zipName )
        , dest = build.resolve( build.openframeworks.root )

    build.log('unzip', source, dest )
    // return fs.ensureDir( dest )
    // .then( () => require('decompress')( source, dest, {
    //   plugins: [ require('decompress-unzip') ],
    //   strip: 1
    // }).then())
    const Decompress = require('decompress')
    var decompress = new Decompress({mode: '755'})
      .src( source )
      .dest( dest )

    switch ( os.platform() ) {
      case 'darwin':
        decompress = decompress.use(Decompress.zip({strip: 1}))
      break

      case 'linux':
        decompress = decompress.use(Decompress.targz({strip: 1}))
      break
    }

    return Promise.fromCallback( ( callback ) => decompress.run( callback ) )

    // return Promise.fromCallback( ( callback ) => require('extract-zip')( source, {
    //   dir: dest
    // }, callback ) )
  }

  function patchOF() {
    if ( os.platform() != 'linux' )
      return

    build.log('# patching openFrameworks' )
    return Promise.map( [ 'linuxarmv6l','linuxarmv7l' ], function ( arch ) {
      let src  = build.resolve( build['openframeworks'], 'scripts','templates','linux','qtcreator.qbs' )
      let dest = build.resolve( build['openframeworks'], 'scripts','templates', arch,'qtcreator.qbs' )
      build.log('cp', src, dest )
      return fs.copyAsync( src, dest )
    } )
  }
}
