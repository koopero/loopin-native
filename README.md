**loopin-native** is a module to wrap the compilation and execution of Loopin's shared native binary. It abstracts platform-specific details and makes building the binary as transparent as possible. The following operations are performed:

* Download the latest [openFrameworks](http://openframeworks.cc) release.
* Use `git` to download [ofxLoopin](https://github.com/koopero/ofxLoopin#README), as well as [ofxJSON](https://github.com/jefftimesten/ofxJSON) and [ofxSyphon](https://github.com/astellato/ofxSyphon).
* Creates a new openFrameworks project named 'Loopin', using openFrameworks' project generator.
* Overwrite `main.cpp` and add some default files.
* Compile the binary using `make`.
* Optionally run the binary and return the process.


Currently, the root for all builds is `~/_loopin`. Although `~/.loopin` would be preferred, the dot seems to give OF's build process some grief.

# Requirements

For this module to work, you need a build environment capable of compiling
[openframeworks](http://openframeworks.cc/).

*TODO*

## OSX

[Homebrew](http://brew.sh/) is highly recommended.  [MacPorts](https://www.macports.org/) may also work, but it's not as slick.

*TODO: I need to run this on a fresh, unprepared Mac to see if I'm missing anything.*

## General Dev

Obviously, you're going to need [node](https://nodejs.org/en/) and [npm](https://docs.npmjs.com/getting-started/installing-node).

On linux systems, you'll need to install [build-essential](http://packages.ubuntu.com/trusty/build-essential), or your distribution's equivalent.

Finally, you'll need [git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git). This should be easy to install using your system's package manager.

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

## Windows

Sorry, at this point there is no support for Windows. Although running on Windows should be a matter of some additional configuration, documentation and maybe hammering out some path delimiter issues, I have neither the resources or the desire to do it at this time. *Frankly, I kind of hate Windows.*

If you would like to help getting Loopin running on Windows, please contact me and we'll figure it out.

# Usage

``` sh
npm install -g loopin-native

# Builds Loopin native binary under ~/_loopin
loopin-native --verbose
```

# ofxLoopin Development

If you would like to contribute to the development of **ofxLoopin**, or experiment with the source code, you will need to set up your dev environment a bit differently.

``` sh
# ~/PROJECTHOME is the directory where you keep you code.
cd ~/PROJECTHOME

# Clone a fresh copy of the ofxLoopin source
git clone --recursive https://github.com/koopero/ofxLoopin.git ofxLoopin

# Delete the previously downloaded version of the ofxLoopin library
rm -rf ~/_loopin/native/lib/openframeworks/addons/ofxLoopin/

# Link your copy
ln -s ~/PROJECTHOME/ofxLoopin ~/_loopin/native/lib/openframeworks/addons/ofxLoopin
```

You should now be set up to make changes to the ofxLoopin library. For easier development, make the following change in your project:

``` js

loopin.plugin('bootstrap', {
  // This will tell loopin-native to run `make` every time it runs.
  quick: false,

  // (Optional) Trace compiler output to the console
  verbose: true
})
```



# Sister Projects
* [loopin](https://github.com/koopero/loopin#README) - **JS** Hub project.
* [ofxLoopin](https://github.com/koopero/ofxLoopin#README) - **C++** Loopin openframeworks plugin.
