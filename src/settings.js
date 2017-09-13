module.exports = settings

const _ = require('lodash')
    , path = require('path')
    , platform = require('./settings/platform')
    , files = require('./settings/files')
    , pkg = require('../package.json')


class Settings {
  templatize( path ) {
    let value = _.get( this, path )
    var result

    if ( _.isString( value ) ) {
      var last
      do {
        last = value
        value = value.replace(
          /\$\{\s*([_\w][_\w\d\.]*)\s*\}/g,
          ( all, path ) => _.get( this, path )
        )
      } while( value != last )
      result = value
    }

    if ( _.isObject( value ) ) {
      result = _.map( value, ( v, k ) => this.templatize( path+'.'+k ) )
    }

    _.set( this, path, value )

    return result
  }
}

const OPTIONS = require('boptions')({
  'root': '',
  'title': 'ofxLoopin',
  'version': pkg.version,
  'dev': false,
  'quiet': true,
  'verbose': false,
  'useEnv': true,
  'addons': {}
})

function settings( options ) {
  const settings = new Settings()
  _.defaults( settings, OPTIONS( arguments ) )


  let root = options.root ||
    ( settings.useEnv && process.env['LOOPIN_NATIVE_DEV'] ) || ''

  root = path.resolve( root )
  settings.root = root

  //
  // Platform
  //
  settings.platform = options.platform || platform.defaultPlatform()
  platform.validatePlatform( settings.platform )


  //
  // Full name
  //
  settings.name = `${settings.title}-${settings.version}-${settings.platform}`

  //
  // Files
  //
  files.loadSettingsFiles( settings )

  settings.templatize('openframeworks')
  settings.templatize('project')
  settings.templatize('binary')

  settings.templatize = settings.templatize

  _.merge( settings, {
    openframeworks: {
      zipPath: path.join('download', settings.openframeworks.zipName ),
      root: path.join('lib',`of_v${settings.openframeworks.version}_${settings.platform}_release`)
    }
  })

  Object.freeze( settings )
  return settings
}
