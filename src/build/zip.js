module.exports = zip
const Promise = require('bluebird')
    , zipdir = require('zip-dir')
    , fs = require('fs-extra')

function zip( build ) {
  build.templatize('binary.package')

  let filelist = [ 'data', build.binary.package ]

  // filelist = filelist.map( file => build.resolve( build.project.root, 'bin', file ) )

  console.log( filelist )

  return fs.mkdirs( build.resolve( build.upload.dir ) )
  .then( () => require('tar').c( {
    file: build.resolve( build.upload.dir, build.project.zipName ),
    cwd: build.resolve( build.project.root, 'bin' ),
    gzip: true,
    follow: true,
    portable: false,
  }, filelist ) )

  // .then( () => Promise.fromCallback( function ( callback ) {
  //   const zipName = build.templatize( 'project.zipName' )
  //   build.log('zip', zipName )
  //   zipdir(
  //     build.resolve( build.project.root, 'bin' ),
  //     {
  //       saveTo: build.resolve( build.upload.dir, zipName ),
  //       filter: (path, stat) => !/\.zip$/.test(path)
  //     },
  //     callback
  //   )
  // }))
}
