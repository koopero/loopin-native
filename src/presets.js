module.exports = presets

const fs = require('fs')
    , pathlib = require('path')
    , yaml = require('js-yaml')
    , filewatcher = require('filewatcher')


function presets( presets, root ) {
  const result = {}
      , files = result.files =
          presets.map( ( preset ) => findFile ( preset, root ) )
          .filter( (a)=>!!a )


  result.load = function () {
    const data = files.map( loadFile )
      .filter( ( a ) => !!a )

    return serialize( data )
  }

  var watcher

  result.watch = function ( write ) {
    if ( !watcher ) {
      watcher = filewatcher()
      files.map( ( file ) => watcher.add( file ) )
    }

    watcher.on('change', function( file ) {
      write( serialize( [ loadFile( file )]))
    } )

    return watcher
  }

  return result
}

function findFile( preset, root ) {
  var file = tryFile( preset )
          || tryFile( process.cwd(), preset )
          || tryFile( 'preset', preset + '.yaml' )

  if ( file ) file = pathlib.resolve( file )

  return file
}

function tryFile() {
  var path = pathlib.join.apply( null, arguments )
  try {
    path = pathlib.resolve(path)
    fs.accessSync( path, fs.R_OK )

    if ( fs.statSync( path ).isFile() ) {
      return path
    }
  } catch ( e ) {

  }

  return null
}

function loadFile( path ) {
  console.log( 'loadFile', path )
  var data

  try {
    data = fs.readFileSync( path, 'utf8' )
    data = yaml.load( data )
  } catch ( e) {
    return ''
  }

  return data
}

function serialize( data ) {
  data = data.filter( ( preset ) => !!preset )
  data = data.map( ( preset ) => JSON.stringify( preset ) )
  data = data.join('\n')
  if ( data )
    data += '\n'
  return data
}
