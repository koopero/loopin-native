const fs = require('fs-extra')
    , path = require('path')

exports.scratch = ( p ) => path.resolve( __dirname, 'scratch', p || '' )
exports.root = ( p ) => path.resolve( __dirname, '..', p || '' )
