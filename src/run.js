module.exports = run

const _ = require('lodash')

function run( opt ) {
  const build = this
      , execPath = build.resolve( build.app, build.substitute( build.settings['app']['executable'] ) )
      , spawn = require('child_process').spawn

  build.log( execPath )
  const process = spawn( execPath, [], { cwd: opt.cwd } )
  build.process = process
}
