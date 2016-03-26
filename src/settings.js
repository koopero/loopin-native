module.exports = require('js-yaml').load( require('fs').readFileSync( require('path').resolve(__dirname,'../settings.yaml'), 'utf8' ) )
