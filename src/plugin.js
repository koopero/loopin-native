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
    options = _.merge( { verbose: true }, options )
    _.defaults( options, {
      cwd: loopin.filesAbsolute()
    })

    return Promise.resolve( resolveProcess() )
    .then( function ( process ) {
      loopin.plugin( require('./stdio'), {
        proc: process,
        verbose: !!options.verbose
      } )
      process.on('close', event => onChildClose( process, event ) )
      loopin.dispatchEvent( { path: 'native', type: 'open', data: { pid: process.pid } } )
      loopin.emit( 'open' )

      killOnExit( process )

    } )

    function resolveProcess() {
      if ( options.process )
        return options.process

      const settings = require('./settings')( options )
          , build = require('./builder')( settings )

      return require('./build/run')( build )
    }
  }

  function onChildClose( process, event ) {
    loopin.close()
  }

  function killOnExit( childProcess ) {
    process.on('exit', event => childProcess.kill() )
  }



}
