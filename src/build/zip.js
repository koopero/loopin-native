module.exports = zip
const Promise = require('bluebird')
    , fs = require('fs-extra')

function zip( build ) {
  build.templatize('binary.package')

  let filelist = [ 'data', build.binary.package ]

  return fs.mkdirs( build.resolve( build.upload.dir ) )
  .then( () => require('tar').c( {
    file: build.resolve( build.upload.dir, build.project.zipName ),
    cwd: build.resolve( build.project.root, 'bin' ),
    gzip: true,
    follow: true,
    portable: false,
  }, filelist ) )

}
