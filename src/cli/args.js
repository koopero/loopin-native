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

parser.addArgument(
  ['--deps'],
  {
    help: 'Install openframeworks dependencies and exit. Will require root.',
    action: 'storeTrue'
  }
)


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
  ['-q', '--quiet'],
  {
    help: 'Log as little as possible',
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
  ['--zip'],
  {
    help: 'Zip binary for upload.',
    action: 'storeTrue'
  }
)

parser.addArgument(
  ['--json'],
  {
    help: 'Output as JSON',
    action: 'storeTrue'
  }
)

parser.addArgument(
  ['--info'],
  {
    help: 'Get Loopin system info and exit.',
    action: 'storeTrue'
  }
)

module.exports = parser.parseArgs()
