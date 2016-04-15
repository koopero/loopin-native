module.exports = addons

const _ = require('lodash')
    , Promise = require('bluebird-extra')
    , fs = Promise.promisifyAll( require('fs-extra'))
    , path = require('path')

function addons() {
  const build = this

  return Promise.mapSeries( _.keys( build.addons ), addonKey )

  function addonKey( key ) {
    var addon = build.addons[key]

    if ( _.isString( addon ) )
      build.addons[key] = addon = { path: addon }


    addon['dest'] = build.resolve( build.openframeworks, 'addons/'+key )

    build.log('#addon', key )

    if ( exists() ) {
      return
    } else if ( addon['git'] ){
      return gitClone()
    } else if ( addon['path'] ){
      return link()
    }

    function link () {
      build.log( 'ln -s', addon['path'], addon['dest'] )
      return fs.ensureSymlinkAsync( addon['path'], addon['dest'] )
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

    function exists() {
      return fs.existsSync( addon['dest'] )
    }
  }
}
