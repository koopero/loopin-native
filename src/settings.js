module.exports = settings

const _ = require('lodash')
    , path = require('path')
    , platform = require('./settings/platform')
    , files = require('./settings/files')
    , pkg = require('../package.json')


class Settings {
  templatize( path ) {
    let value = _.get( this, path )

    if ( _.isString( value ) ) {
      var last
      do {
        last = value
        value = value.replace(
          /\$\{\s*([_\w][_\w\d\.]*)\s*\}/g,
          ( all, path ) => _.get( this, path )
        )
      } while( value != last )
    }

    if ( _.isObject( value ) ) {
      _.map( value, ( v, k ) => this.templatize( path+'.'+k ) )
    }

    _.set( this, path, value )
  }
}

function settings( options ) {
  var settings = new Settings()

  let root = options.root || process.env['LOOPIN_NATIVE'] || './loopin-native'
  root = path.resolve( root )
  settings.root = root
  //
  // Name
  //
  settings.title = _.isString( options.title ) ? options.title : 'Loopin'

  //
  // Platform
  //
  settings.platform = options.platform || platform.defaultPlatform()
  platform.validatePlatform( settings.platform )

  //
  // Version
  //
  settings.version = pkg.version

  //
  // Full name
  //
  let name = settings.name = `${settings.title}-${settings.version}-${settings.platform}`

  //
  // Files
  //
  files.loadSettingsFiles( settings )

  settings.templatize('openframeworks.zipName')
  settings.templatize('project')
  settings.templatize('binary')



  _.merge( settings, {
    openframeworks: {
      zipPath: path.join('download', settings.openframeworks.zipName ),
      root: path.join('lib',`of_v${settings.openframeworks.version}_${settings.platform}_release`)
    }
  })

  Object.freeze( settings )
  return settings
}
