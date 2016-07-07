module.exports = presets

const fs = require('fs')
    , pathlib = require('path')
    , yaml = require('js-yaml')


function presets( presets, root ) {
  presets = presets.map( resolvePreset )
  presets = presets.filter( ( preset ) => !!preset )
  presets = presets.map( ( preset ) => JSON.stringify( preset ) )
  presets = presets.join('\n')
  if ( presets )
    presets += '\n'
  return presets
}

function resolvePreset( preset ) {
  var data = null
    || loadFile( preset )
    || loadFile( process.cwd(), preset )
    || loadFile( 'preset', preset + '.yaml' )

  try {
    return yaml.load( data )
  } catch ( e ) {
    return ''
  }
}

function loadFile() {
  var path = pathlib.join.apply( null, arguments )

  try {
    return fs.readFileSync( path, 'utf8' )
  } catch ( e) {
    return null
  }
}
