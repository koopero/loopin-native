const fs = require('fs-extra')
    , path = require('path')

exports.scratch = ( p ) => path.resolve( __dirname, 'scratch', p || '' )
