module.exports = { loadSettingsFiles }


const _ = require('lodash')
    , fs = require('fs')
    , path = require('path')
    , yaml = require('js-yaml')

function loadSettingsFiles ( settings ) {
  const platform = settings.platform

  _.merge( settings, loadSettingsFile( 'common' ) )

  if ( platform.startsWith('linux') )
    _.merge( settings, loadSettingsFile( 'linux' ) )

  _.merge( settings, loadSettingsFile( platform ) )

  return settings
}


function loadSettingsFile( key ) {
  const source = fs.readFileSync( path.resolve( __dirname, '..', '..', 'settings', key+'.yaml' ), 'utf8' )
      , data = yaml.load( source )

  return data
}
