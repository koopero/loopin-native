module.exports = executable

const Promise = require('bluebird')

async function executable( build ) {
  let executable = build.project.executable

  build.log( '# checking for executable ', executable )

  return Promise.resolve()
  .then( () => build.dev || !build.checkFile( build.project.executable ) )
  .then( function ( needExecutable ) {
    if ( needExecutable ) {
      if ( build.dev ) {
        return require('./devEnv.js')( build )
        .then( () => require('./make.js')( build ) )
      } else {
        return require('./download')( build )
        .catch( err => {
          build.log('# Failed to download pre-packaged binary. Falling back to source build.', err )
          process.exit()
          return require('./devEnv.js')( build )
          .then( () => require('./make.js')( build ) )
        } )
      }
    }
  } )
  .then( () => build.resolve( build.project.executable ) )
}
