/*
  Parser for command line arguments.
*/

const argparse = require('argparse')
    , pkg = require('../../package.json')
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

// parser.addArgument([ 'preset' ], {
//   nargs: '*',
//   help: 'Load preset files'
// })

parser.addArgument(
  ['-e', '--env'],
  {
    help: 'Show environment variables and exit.',
    action: 'storeTrue'
  }
)

parser.addArgument(
  ['-d', '--dev'],
  {
    help: 'Rig for development.',
    action: 'storeTrue'
  }
)

parser.addArgument(
  ['-x', '--run'],
  {
    help: 'Run ofxLoopin.',
    action: 'storeTrue'
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
  ['-T', '--test'],
  {
    help: 'Perform a simple self-test.',
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
  ['--zip'],
  {
    help: 'Zip binary for upload.',
    action: 'storeTrue'
  }
)



module.exports = parser.parseArgs()
