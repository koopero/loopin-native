module.exports = run

function run() {
  const build = this
      , execPath = build.resolve( build.app, build.substitute( build.settings['app']['executable'] ) )
      , spawn = require('child_process').spawn

  build.log( execPath )
  const process = spawn( execPath, [], { } )
  build.process = process
}
