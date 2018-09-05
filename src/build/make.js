module.exports = make
function make( build ) {
  const root = build.resolve( build.project.root )
  const make = build.make || 'make'
  build.log( 'cd', root  )

  return require('./project')( build )
  .then( () => build.command( make, [], { cwd: root } ) )
  .then( () => build )
}
