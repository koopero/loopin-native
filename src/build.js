module.exports = build

const settings = require('./settings')

const _ = require('lodash')
    , Promise = require('bluebird')
    , boptions = require('boptions')
    , fs = Promise.promisifyAll( require('fs-extra'))
    , path = require('path')
    , Download = require('download')
    , downloadStatus = require('download-status')

function build( opt ) {

  opt.addons = _.merge( _.clone( settings['addons'] ), opt.addons )

  return ensureLibs( opt )
    .then( () => ensureProject( opt ) )
    .then( () => makeApp( opt ) )
    .then( () => runApp( opt ) )


}

function log( opt, data ) {
  console.log( data )
}


function error( opt, data ) {
  console.error( data )
}

function ensureLibs( opt ) {
  return ensureOpenframeswork()
    .then( Promise.mapSeries( _.keys( opt.addons ), ensureAddon ) )

  function ensureOpenframeswork() {

    opt.openframeworks = opt.openframeworks || path.resolve( opt.root, 'lib/openframeworks' )

    return ensure()

    function ensure ( ) {
      if ( exists() && !opt.clean )
        return Promise.resolve( opt )

      return ensureZip()
        .then( unpack )
        .then( () => opt )
    }

    function exists() {

      // Random file in the openFrameworks directory
      const file = './CODE_OF_CONDUCT.md'

      return fs.existsSync( resolve( file ) )
    }

    function ensureZip( ) {
      const version  = settings['openframeworks']['version']
          , platform = require('./platform')
          , stringsub = require('string-substitute')
          , zip_name = stringsub( settings['openframeworks']['zip_name'], version, platform )
          , release_url = stringsub( settings['openframeworks']['release_url'], version, platform )
          , tmp = path.resolve( opt.root, 'tmp/' )


      opt.openframeworksZip = opt.openframeworksZip || path.resolve( tmp, zip_name )

      if ( fs.existsSync( opt.openframeworksZip ) )
        return Promise.resolve( true )

      var download = new Download({strip: 1})
        	.get( release_url, tmp )
        	.use(downloadStatus())

      return Promise.fromCallback( ( callback ) => download.run( callback ) )
    }

    function unpack() {
      const Decompress = require('decompress');
      const decompress = new Decompress({mode: '755'})
      	.src(opt.openframeworksZip)
      	.dest(opt.openframeworks)
      	.use(Decompress.zip({strip: 1}))

      return Promise.fromCallback( ( callback ) => decompress.run( callback ) )
    }

    function resolve() {
      return path.resolve.bind( null, opt.openframeworks ).apply( null, arguments )
    }
  }

  function ensureAddon( key ) {

    var addonOpt = opt.addons[key]

    if ( _.isString( addonOpt ) )
      opt.addons[key] = addonOpt = { path: addonOpt }


    addonOpt['dest'] = path.resolve( opt.openframeworks, 'addons/'+key )

    console.log('Installing addon', key )

    if ( exists() ) {
      return Promise.resolve( opt )
    } else if ( addonOpt['git'] ){
      return gitClone()
    } else if ( addonOpt['path'] ){
      return link()
    }

    function link () {
      return fs.ensureSymlinkAsync( addonOpt['path'], addonOpt['dest'] )
    }

    function gitClone() {
      const cmd = 'git'
          , args = [
            'clone',
            '--recursive',
            addonOpt['git'],
            addonOpt['dest']
          ]

      return command( cmd, args )
    }

    function exists() {
      return fs.existsSync( addonOpt['dest'] )
    }
  }
}


function command( cmd, args, opt ) {
  opt = opt || {}
  // opt.stdio = [ 'ignore', process.stdio, process.stderr ]

  const spawn = require('child_process').spawn

  return Promise.fromCallback( function ( cb ) {
    const process = spawn( cmd, args, opt )
    console.log( cmd, args.join(' ') )

    process.stdout.on('data', (d) => log( opt, String( d ) ) )
    process.stderr.on('data', (d) => error( opt, String( d ) ))

    process.on('close', function ( code ) {
      if ( code ) {
        cb( 'non zero code')
      } else {
        cb();
      }
    })
  } )
}

// lib/openframeworks

function ensureProject( opt ) {
  opt.app = opt.app || path.resolve( opt.root, 'app' )

  if ( exists() )
    return Promise.resolve( opt )

  return generate()
    .then( replaceMain )

  function exists() {
    const testfile = path.resolve( opt.app, 'Makefile' )
    return fs.existsSync( testfile )
  }

  function generate() {
    const generator = path.resolve( opt.openframeworks, settings['openframeworks']['projectGenerator'][ require('os').platform() ] )
        , addons = _.keys( opt.addons )
        , args = [
          '-a'+addons.join(','),
          '-o'+opt.openframeworks,
          opt.app
        ]

    return command( generator, args )
  }

  function replaceMain() {
    const appSrcPath = path.resolve( opt.app, 'src' )
        , appMain = path.resolve( appSrcPath, 'main.cpp' )
        , replacementMain = path.resolve( opt.addons.ofxLoopin.dest, 'replace/main.cpp' )

    console.log( "Replace", replacementMain, appMain )
    return fs.copyAsync( replacementMain, appMain )
  }
}


function makeApp( opt ) {
  const appPath = opt.app

  return command( 'make', [], { cwd: appPath } )
}

function runApp( opt ) {
  const execPath = path.resolve( opt.app, settings['app']['executable'][ require('os').platform() ] )
      , spawn = require('child_process').spawn

  console.log('Running app', execPath )

  return spawn( execPath, [], { detached: true } )
}
