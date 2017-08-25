module.exports = run

const _ = require('lodash')
    , os = require('os')

function run( opt ) {
  const build = this
      , spawn = require('child_process').spawn
      , env = _.clone( process.env )

  let execPath = build.resolve( build.app, build.substitute( build.settings['app']['executable'] ) )


  // Try to connect to main screen on linux systems
  if ( os.platform() == 'linux' && !env['DISPLAY'] )
    env['DISPLAY'] = ':0'

  // execPath += '_debug'
  build.log( execPath )
  const proc = spawn( execPath, [], { cwd: opt.runCwd, env: env } )
  // const proc = spawn( 'catchsegv', [ execPath ], { cwd: opt.runCwd, env: env } )

  build.process = proc
}
