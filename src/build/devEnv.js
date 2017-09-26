
const Promise = require('bluebird')
function devEnv( build ) {
  return Promise.resolve()
    .then( () => require('./openframeworks')( build ) )
    .then( () => require('./addons')( build ) )
    .catch( function ( e ) {
      console.error( build.stderr || '' )
      throw e
    })
    .then( () => build )
}
module.exports = devEnv
