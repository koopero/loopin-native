
const native = require('./builder')
    , yaml = require('js-yaml')
    , argparse = require('argparse')
    , pkg = require('../package.json')
    , parser = new argparse.ArgumentParser({
        version: pkg.version,
        addHelp: true,
      })

addArgparseArguments( parser )


const opt = parser.parseArgs()


var presets = require('./presets')( opt.preset )

native( opt )
.then( function ( build ) {
  _process = build.process

  if ( _process ) {
    _process.stdout.pipe( process.stdout )
    _process.stderr.pipe( process.stderr )
    process.stdin.pipe( _process.stdin )

    if ( presets ) {
      console.log('writing preset', presets )
      _process.stdin.write( presets )
    }
  }
} )

process.on('exit', function () {
  if ( _process )
    _process.kill()
})


function addArgparseArguments( parser ) {
  parser.addArgument(
    ['-r', '--run'],
    {
      help: 'Run the Loopin exec',
      action: 'storeTrue'
    }
  )

  parser.addArgument(
    ['--verbose'],
    {
      help: 'Log everything',
      action: 'storeTrue'
    }
  )

  parser.addArgument(
    ['-q', '--quiet'],
    {
      help: 'Do not log anything',
      action: 'storeTrue'
    }
  )

  parser.addArgument(
    ['-d', '--dir'],
    {
      help: 'Working directory',
      action: 'storeTrue'
    }
  )

  parser.addArgument([ 'preset' ], {
    nargs: '*',
    help: 'Load preset files'
  });

}
