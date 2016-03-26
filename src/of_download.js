const settings = require('./settings')
    , platform = require('./platform')
    , version  = settings['openframeworks']['version']

const stringsub = require('string-substitute')

exports.url = stringsub( settings['openframeworks']['release_url'], version, platform )
