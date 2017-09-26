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


// /Volumes/hdd/koop/loopin/loopin-native/tmp/loopin-native/ofxLoopin-0.8.0a-osx/bin/ofxLoopin-0.8.0a-osx.app/Contents/MacOS/ofxLoopin-0.8.0a-osx
// /Volumes/hdd/koop/loopin/loopin-native/tmp/loopin-native/ofxLoopin-0.8.0a-osx/bin/ofxLoopin.app/Contents/MacOS/ofxLoopin
