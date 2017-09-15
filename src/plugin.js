module.exports = loopinNative

const _ = require('lodash')

function loopinNative( options ) {
  const loopin = this
      , Promise = loopin.Promise

  loopin.plugin('files')
  loopin.plugin('bootstrap')

  loopin.hookAdd('bootstrap', () => start( options ) )

  return

  function start( options ) {
    options = _.merge( {}, options )
    _.defaults( options, {
      cwd: loopin.filesAbsolute()
    })

    const Promise = require('bluebird')
        , settings = require('./settings')( options )
        , build = require('./builder')( settings )

    var promise = Promise.resolve()

    return Promise.resolve()
    .then( () => require('./build/executable')( build ) )
    .then( () => require('./build/run')( build ) )
    .then( function ( process ) {
      loopin.plugin( 'stdio', process )
      loopin.dispatchEvent( { path: 'native', type: 'open', data: { pid: process.pid } } )
      loopin.emit( 'open' )
    } )
  }

}
