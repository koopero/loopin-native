module.exports = addons

const _ = require('lodash')
    , Promise = require('bluebird-extra')
    , fs = Promise.promisifyAll( require('fs-extra'))
    , path = require('path')

function addons( build ) {
  return Promise.mapSeries( _.keys( build.addons ), addonKey )

  function addonKey( key ) {
    var addon = build.addons[key]

    if ( _.isString( addon ) )
      build.addons[key] = addon = { path: addon }


    addon['dest'] = build.resolve( build.openframeworks.root, 'addons/'+key )


    build.log('#addon', key )

    if ( exists() ) {
      return
    } else if ( addon['git'] ){
      return gitClone()
      .then( gitCheckout )
      .then( gitPatch )

    } else if ( addon['packageLink'] ){
      // If path is specified, then the addon is probably
      // ofxLoopin, which is included locally.
      return link()
    }

    function link () {
      var addonPath = path.resolve( __dirname, '..', '..', addon['packageLink'] )
      build.log( 'ln -s', addonPath, addon['dest'] )
      return fs.ensureSymlinkAsync( addonPath, addon['dest'] )
    }

    function gitClone() {
      const cmd = 'git'
          , args = [
            'clone',
            '--recursive',
            addon['git'],
            addon['dest']
          ]

      return build.command( cmd, args )
    }

    function gitPatch() {
      if ( !addon['patch'] )
        return

      return

      const cmd = 'git'
          , args = [
            'apply',
            addon['commit']
          ]

      return build.command( cmd, args, { cwd: addon['dest'] } )
    }

    function gitCheckout() {
      if ( !addon['commit'] )
        return

      const cmd = 'git'
          , args = [
            'checkout',
            addon['commit']
          ]

      return build.command( cmd, args, { cwd: addon['dest'] } )
    }

    function exists() {
      return fs.existsSync( addon['dest'] )
    }
  }
}
