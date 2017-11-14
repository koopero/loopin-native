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

    return Promise.resolve( resolveProcess() )
    .then( function ( process ) {
      loopin.plugin( require('./stdio'), {
        proc: process,
        verbose: !!options.verbose
      } )
      loopin.dispatchEvent( { path: 'native', type: 'open', data: { pid: process.pid } } )
      loopin.emit( 'open' )
    } )

    function resolveProcess() {
      if ( options.process )
        return options.process

      const settings = require('./settings')( options )
          , build = require('./builder')( settings )

      return require('./build/executable')( build )
      .then( () => require('./build/run')( build ) )
    }
  }

}
