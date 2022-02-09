const Diff = require('diff')
const _ = require('lodash')
const Promise = require('bluebird')
const pathlib = require('path')
const fs = require('fs-extra')

module.exports = main

async function main( build, {
  patches,
  dir,
} ) {
  await Promise.mapSeries( patches, async ( name ) => {

    let file = pathlib.resolve( __dirname, '..', 'patch', name )
    let patch = await fs.readFile( file, 'utf8' )

    build.log( `# applying patch ${name}`)

    await Promise.fromCallback( cb => {
      Diff.applyPatches( patch, { loadFile, patched, complete } )

      function fileForIndex( index ) {
        let { oldFileName } = index
        let file = build.resolve( dir, oldFileName )
        return file
      }

      async function loadFile( index, callback ) {
        console.log( 'loadFile', { index })
        let file = fileForIndex( index )
        let data = await fs.readFile( file, 'utf8' )
        callback( null, data )        
      }

      async function patched( index, content, callback ) {
        console.log( 'patched', { index, content })
        let file = fileForIndex( index )
        await fs.writeFile( file, content )
        callback()
      }

      function complete( err ) {
        cb( err )
      }
    } )
  })
  
}
