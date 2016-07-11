
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

if ( opt.clean ) {
  const fs = require('fs-extra')
      , userhome = require('userhome')
      , del = userhome('_loopin','native' )

  console.log( 'rm -rf '+del )
  fs.removeSync( del )
}

var presets = require('./presets')( opt.preset )
var presetData = presets.load()

if ( opt.test ) {
  presetData += '{"text":{"test":"Loopin Lives!"},"show":"test"}\n'
}

var _process

native( opt )
.then( function ( build ) {
  _process = build.process

  const write = ( str ) => _process && _process.stdin.write( str )
  write( presetData )

  if ( opt.watch )
    presets.watch( write )

  if ( _process ) {

    _process.stdout.pipe( process.stdout )
    _process.stderr.pipe( process.stderr )
    process.stdin.pipe( _process.stdin )

    _process.on('exit', function () {
      process.exit()
    })
  }
} )

process.on('exit', function () {
  if ( _process )
    _process.kill()
})


function addArgparseArguments( parser ) {
  // parser.addArgument(
  //   ['-d', '--dir'],
  //   {
  //     help: 'Working directory',
  //     action: 'storeTrue'
  //   }
  // )

  parser.addArgument(
    ['-n', '--no-run'],
    {
      dest: 'run',
      help: "Don't run the exec after building.",
      action: 'storeFalse'
    }
  )

  parser.addArgument(
    ['-V', '--verbose'],
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

  // parser.addArgument(
  //   ['-i', '--ignore-frame'],
  //   {
  //     help: 'Squelch frame events from output',
  //     action: 'storeTrue'
  //   }
  // )

  parser.addArgument(
    ['-w', '--watch'],
    {
      help: 'Watch preset files',
      action: 'storeTrue'
    }
  )

  parser.addArgument(
    ['-T', '--test'],
    {
      help: 'Run a really simple test preset',
      action: 'storeTrue'
    }
  )

  parser.addArgument(
    ['--clean'],
    {
      help: 'Clean ~/_loopin',
      action: 'storeTrue'
    }
  )



  parser.addArgument([ 'preset' ], {
    nargs: '*',
    help: 'Load preset files'
  });

}
