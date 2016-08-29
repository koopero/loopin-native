const _ = require('lodash')
    , fs = require('fs')
    , path = require('path')
    , yaml = require('js-yaml')
    , pkg = require('../package.json')


const settings = {}

settings.version = pkg.version
_.merge( settings, loadSettingsFile( 'common' ) )

try {
  _.merge( settings, loadSettingsFile( require('os').platform() ) )
} catch ( e ) {
  throw new Error('Your platform is not yet supported.')
}

module.exports = settings

function loadSettingsFile( key ) {
  const source = fs.readFileSync( path.resolve( __dirname, '..', 'settings', key+'.yaml' ), 'utf8' )
      , data = yaml.load( source )

  return data
}
