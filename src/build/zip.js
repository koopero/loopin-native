module.exports = zip

const Promise = require('bluebird')
const fs = require('fs-extra')
const tar = require('tar')
const glob = require('glob-promise')

async function zip( build ) {
  build.templatize('binary.package')


  await require('./executable')( build )

  let cwd = build.resolve( build.project.root, 'bin' )
  let filelist = await glob( '*', { cwd } )

  await fs.mkdirs( build.resolve( build.upload.dir ) )
  
  await tar.c( {
    file: build.resolve( build.upload.dir, build.project.zipName ),
    cwd,
    gzip: true,
    follow: true,
    portable: false,
  }, filelist )
}
