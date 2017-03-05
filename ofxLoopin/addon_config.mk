meta:
	ADDON_NAME = ofxLoopin
	ADDON_DESCRIPTION = openFrameworks Loopin Renderer
	ADDON_AUTHOR = Samm Zuest Cooper
	ADDON_TAGS = "loopin"
	ADDON_URL = http://github.com/koopero/ofxLoopin

common:
	ADDON_DEPENDENCIES = ofxJSON
	ADDON_INCLUDES = src
	ADDON_DATA = bin/data/passthru.vert.glsl
	ADDON_SOURCES_EXCLUDE = src/ofxLoopinAudioAnalyzer.cpp
