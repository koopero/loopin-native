module.exports = make
function make() {
  const build = this

  build.log( 'cd', build.app )

  return build.command( 'make', ['Debug'], { cwd: build.app } )
}
