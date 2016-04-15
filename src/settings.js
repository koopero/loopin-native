const _ = require('lodash')
    , fs = require('fs')
    , path = require('path')
    , yaml = require('js-yaml')
    , source = fs.readFileSync( path.resolve( __dirname, '../settings.yaml' ), 'utf8' )
    , data = yaml.load( source )
    , platform = require('os').platform()
    , common = data['common']
    , specific = data[platform]

if ( !specific )
  throw new Error('Your platform is not supported.')

module.exports = _.merge( common, specific )
