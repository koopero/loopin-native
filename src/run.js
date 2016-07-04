module.exports = run

const _ = require('lodash')

function run( opt ) {
  const build = this
      , execPath = build.resolve( build.app, build.substitute( build.settings['app']['executable'] ) )
      , spawn = require('child_process').spawn
      , env = _.clone( process.env )

  // Try to connect to main screen on linux systems
  if ( os.platform() == 'linux' && !env['DISPLAY'] )
    env['DISPLAY'] = ':0'

  build.log( execPath )
  const proc = spawn( execPath, [], { cwd: opt.runCwd, env: env } )
  build.process = proc
}
