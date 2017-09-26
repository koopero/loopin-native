module.exports = make
function make( build ) {
  const root = build.resolve( build.project.root )
  build.log( 'cd', root  )

  return build.command( 'make', [], { cwd: root } )
  .then( () => build )
}
