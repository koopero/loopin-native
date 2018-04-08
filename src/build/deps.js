module.exports = deps

const isRoot = require('is-root')
const Promise = require('bluebird')
const getos = Promise.promisify( require('getos') )
const os = require('os')


async function deps( build ) {
  if ( os.platform() != 'linux' ) {
    console.error('--deps is only required on linux')
    process.exit(1)
  }


  if ( !isRoot() ) {
    console.error('--deps must be run as root or with sudo')
    process.exit(1)
  }

  await require('./openframeworks')( build )

  let distro = await getos() 
  distro = distro['dist'].toLowerCase()
  distro = distro.split(/[^\w]/)
  distro = distro[0]


  const cwd = build.resolve( build.openframeworks.root, 'scripts', 'linux', distro )
  let commands = [
    'install_codecs.sh',
    'install_dependencies.sh',
  ]

  for ( let command of commands ) {
    console.log( "# Running OF dep installed. User input may be required." )
    
    command = build.resolve( cwd, command )
    console.log( command )
    await build.command( command, ['-y'], { cwd, stdio: [ process.stdin, process.stdout, process.stderr ] } )
  }

  // console.log( cwd )
  

  // process.exit()


  // build.log( 'cd', cwd  )

  // return require('./openframeworks')( build )
  // .then( () => build.command( 'make', [], { cwd: cwd } ) )
  // .then( () => build )
}
