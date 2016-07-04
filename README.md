# Requirements

For this module to work, you need a build environment capable of compiling
[openframeworks](http://openframeworks.cc/).

*TODO*

## Mac OS

[Homebrew](http://brew.sh/) should include everything needed to build on Mac.

*TODO*: I need to run this this on a fresh, unprepared Mac.

## Linux

*Tested on Linux Mint 18 Sarah*.

### openframeworks Dependencies

To install openframeworks dependencies, first attempt to build `loopin-native` using the command `loopin-native --verbose`. This will likely fail, but will first download and unpack openframeworks. Next, run the following:

``` sh
# You may need to replace 'ubuntu' with your distribution.
cd ~/_loopin/native/lib/openframeworks/scripts/linux/ubuntu

# openframeworks scripts to auto-install dependencies
sudo ./install_dependencies.sh
sudo ./install_codecs.sh
```

Hopefully, this will set up everything required to build openframeworks. Re-run `loopin-native --verbose` to attempt the build again.


# Installation

``` sh
npm install -g loopin-native

# Builds Loopin native binary under ~/_loopin
loopin-native --verbose
```

#

# Projects
* [loopin](https://github.com/koopero/loopin#README) - **JS** Hub project.
* [ofxLoopin](https://github.com/koopero/ofxLoopin#README) - **C++** Loopin openframeworks plugin.
