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
      }
    }
  } )
  .then( () => build.resolve( build.project.executable ) )
}
