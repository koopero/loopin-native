/*
  Parser for command line arguments.
*/
module.exports = parseArgs

function parseArgs() {
  const argparse = require('argparse')
      , pkg = require('../package.json')
      , parser = new argparse.ArgumentParser({
          version: pkg.version,
          addHelp: true,
        })

  parser.addArgument(
    ['-r','--root'],
    {
      help: 'Working directory',
      nargs: '?'
    }
  )

  parser.addArgument([ 'preset' ], {
    nargs: '*',
    help: 'Load preset files'
  })

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

  parser.addArgument(
    ['-T', '--test'],
    {
      help: 'Run a really simple test preset',
      action: 'storeTrue'
    }
  )

  return parser.parseArgs()
}
