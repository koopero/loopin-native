module.exports = project

const _ = require('lodash')
    , Promise = require('bluebird')
    , path = require('path')
    , fs = Promise.promisifyAll( require('fs-extra'))


function project() {
  const build = this

  if ( !build.appName )
    build.appName = build.settings['app']['name']

  if ( !build.app )
    build.app = build.resolve( build.substitute( build.settings['app']['dir'] ) )

  if ( exists() )
    return Promise.resolve( build )

  return buildGenerator()
    .then( generate )
    .then( replaceMain )
    // .then( copyData )
    .then( symlinkData )


  function exists() {
    const testfile = build.resolve( build.app, 'Makefile' )
    return fs.existsSync( testfile )
  }

  function buildGenerator() {
    const generator =
          build.resolve( build.openframeworks,
            build.settings['openframeworks']['projectGenerator']
          )

    if ( fs.existsSync( generator ))
      return Promise.resolve()

    const cwd =
      build.resolve( build.openframeworks,
        build.settings['openframeworks']['projectGeneratorPath']
      )

    return build.command( 'make', [], { cwd: cwd } )
  }

  function generate() {
    const generator =
          build.resolve( build.openframeworks,
            build.settings['openframeworks']['projectGenerator']
          )
        , addons = _.keys( build.addons )
        , args = [
          '-a'+addons.join(','),
          '-o'+build.openframeworks,
          '-p'+build.platform,
          build.app
        ]

    return build.command( generator, args, build )
  }

  function replaceMain() {
    const appSrcPath = build.resolve( build.app, 'src' )
        , appMain = build.resolve( appSrcPath, 'main.cpp' )
        , replacementMain = build.resolve( build.addons.ofxLoopin.dest, 'replace/main.cpp' )

    return fs.copyAsync( replacementMain, appMain )
  }

  function copyData() {
    const dataSrc = path.resolve( __dirname, '..', 'data' )
        , dataDest = build.resolve( build.app, build.settings['app']['ofxLoopinData'] )

    build.log( '#copyData', src, dest )
    return fs.mkdirpAsync( dataDest )
      .then ( () => glob( build.resolve( dataSrc, '*' ) ) )
      .mapSeries( function ( file ) {
        file = path.relative( dataSrc, file )
        const src = build.resolve( build.addons.ofxLoopin.dest, 'data', file )
            , dest = build.resolve( dataDest, file )

        build.log( 'cp', src, dest )

        return fs.copyAsync( src, dest )
      })
  }

  function symlinkData() {
    const dataSrc = path.resolve( __dirname, '..', 'data' )
        , dataDest = build.resolve( build.app, build.settings['app']['ofxLoopinData'] )

    build.log( '# project data symlink')
    build.log( 'ln -s', dataSrc, dataDest )

    return fs.ensureSymlinkAsync( dataSrc, dataDest )
  }
}
