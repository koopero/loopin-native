module.exports = download

const _ = require('lodash')
    , Promise = require('bluebird')
    , fs = Promise.promisifyAll( require('fs-extra'))
    , got = require('got')

function download( build ) {
  return ensureZip()
  .then( deleteExisting )
  .then( unpack )

  async function ensureZip( ) {
    const zip_name = build.project.zipName
        , releaseURL = build.templatize( 'ofxLoopin.releaseURL' )
        , downloadDir = build.resolve( build.download.dir )
        , dest = build.resolve( downloadDir, zip_name )

    if ( fs.existsSync( build.resolve( downloadDir, zip_name ) ) )
      return Promise.resolve( true )


    build.log('cd', downloadDir )
    build.log('wget', releaseURL )

    let data = await got.get( releaseURL, { 
      // This is somewhat dangerous.
      rejectUnauthorized: false,
      encoding: null
    } )

    data = data.body

    await fs.outputFileAsync( dest, data, null )
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
      gzip: true,
    } ) )
  }

}
