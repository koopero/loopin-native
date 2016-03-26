module.exports = libs

const path = require('path')

function libs( options ) {

  const root = options.root

  if ( !options['openframeworks'] ) {
    options['openframeworks'] = path.resolve( root, 'lib/openframeworks' )
  }
  console.log( options )
}
