module.exports = executable

const Promise = require('bluebird')

function executable( build ) {
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
          build.log('# Failed to download pre-packaged binary. Falling back to source build.')
          return require('./devEnv.js')( build )
          .then( () => require('./make.js')( build ) )
        } )
      }
    }
  } )
  .then( () => build.resolve( build.project.executable ) )
}
