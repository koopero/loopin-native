module.exports = make
function make( build ) {
  const root = build.resolve( build.project.root )
  const make = build.make || 'make'
  const args = build.makeArgs || []
  build.log( 'cd', root  )

  return require('./project')( build )
  .then( () => build.command( make, args, { cwd: root } ) )
  .then( () => build )
}
