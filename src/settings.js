module.exports = settings

const _ = require('lodash')
    , path = require('path')
    , platform = require('./settings/platform')
    , files = require('./settings/files')
    , pkg = require('../package.json')
    , fs = require('fs-extra')


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
  'env': false,
  'addons': {}
})

function settings( options ) {
  const settings = new Settings()
  _.defaults( settings, OPTIONS( arguments ) )

  let root = ( settings.useEnv && process.env['LOOPIN_NATIVE_ROOT'] ) || options.root

  if ( !root ) {
    var moduleRoot = path.resolve( __dirname, '..' )
      , moduleBuildRoot = path.resolve( moduleRoot, 'build/')
    try {
      fs.access( moduleRoot, fs.constants.W_OK )
      root = moduleBuildRoot
    } catch ( err ) {
      throw new Error(`No root defined, and could not access ${moduleRoot}`)
    }
  }

  root = path.resolve( root )
  settings.root = root
  settings.cwd = path.resolve( settings.cwd || '.')

  settings.dev = !!settings.dev || ( settings.useEnv && !!process.env['LOOPIN_NATIVE_DEV'] )

  settings.quiet = !!settings.quiet || !!settings.env

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

  // _.merge( settings, {
  //   openframeworks: {
  //     zipPath: path.join('download', settings.openframeworks.zipName ),
  //     root: path.join('lib',`of_v${settings.openframeworks.version}_${settings.platform}_release`)
  //   }
  // })

  Object.freeze( settings )
  return settings
}
