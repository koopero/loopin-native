module.exports = download

const _ = require('lodash')
    , Promise = require('bluebird')
    , fs = Promise.promisifyAll( require('fs-extra'))
    , glob = Promise.promisify( require('glob') )
    , path = require('path')
    , os = require('os')
    , Download = require('download')
    , downloadStatus = require('download-status')


function download( build ) {
  return ensureZip()
  .then( deleteExisting )
  .then( unpack )

  function ensureZip( ) {
    const zip_name = build.project.zipName
        , release_url = build.templatize( 'ofxLoopin.releaseURL' )
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

  function deleteExisting() {
    const binDir = build.resolve( build.project.root, 'bin' )
    return fs.remove( binDir )
    .then( () => fs.emptyDir(binDir) )
  }

  function unpack() {
    const Decompress = require('decompress')
        , source = build.resolve( build.download.dir, build.project.zipName )
        , dest = build.resolve( build.project.root, 'bin' )

    build.log('unzip', source, dest )

    return fs.mkdirs( dest )
    .then( () => require('tar').x( {
      file: build.resolve( build.download.dir, build.project.zipName ),
      cwd: build.resolve( build.project.root, 'bin' ),
      unlink: true,
      // gzip: true,
      // follow: true,
      // portable: false,
    } ) )

    // var decompress = new Decompress({})
    //   .src( source )
    //   .dest( dest )
    //
    // decompress = decompress.use(Decompress.zip({}))
    //
    // return Promise.fromCallback( ( callback ) => decompress.run( callback ) )
  }

}
