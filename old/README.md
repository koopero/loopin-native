# These docs are obsolete!!


**loopin-native** contains all that is needed to run [Loopin](https://github.com/koopero/loopin)
applications using a share, natively compiled binary. It includes the following:

* C++/[openFrameworks](http://openframeworks.cc) source code for the reference Loopin server implementation (ofxLoopin)
* node.js functions to automatically build and run the The Binary.  *src/\**
* Command-line utility `loopin-native` to manually build The Binary. *src/cli.js*  

# Globals

The files created by this module are shared between all instances of `loopin-native`. This means that all applications which require `loopin-native` or `loopin` will use the same files, greatly reducing compile times.

These files are stored in the directory `~/_loopin`  Although `~/.loopin` would be preferred, the dot seems to give OF's build process some grief.

# Gratitude

`Loopin` would not be possible without the incredible [openFrameworks](http://openframeworks.cc/community/) library. So much gratitude.

# Installation

Please remember that since **loopin-native** downloads and compiles a good amount of code, these procedures may take several minutes.

## OSX

First, you need to install [Homebrew](http://brew.sh/). Next, go to your terminal and run the following:

``` sh
# Install node.js & git via homebrew
brew install node git

# Install loopin-native
npm install -g loopin-native

# Build and run the Loopin binary.
loopin-native -V -T
```

If everything goes well, you should see a window with the text 'Loopin Lives!'

## Linux

*Tested on Mint 18 & Ubuntu 16.10*.

``` sh
# Install prerequisites using apt-get. This may be yum on your machine.
sudo apt-get install build-essential git nodejs npm

# Install the loopin-native module
sudo npm install -g loopin-native

# Try to build the Loopin binary. This will fail, but it will first
# download and unpack openFrameworks.
loopin-native -V -n

# Next, we'll need to install some openFrameworks dependencies.
# ( You may need to replace 'ubuntu' with your distribution )
cd ~/_loopin/native/openFrameworks/0.9.8/scripts/linux/ubuntu

# openframeworks scripts to auto-install dependencies
# You will need to hit 'Y' a number of times.
sudo ./install_dependencies.sh
sudo ./install_codecs.sh

# Note that while most of these deps will be installed globally,
# install_dependencies can also recompile Poco within the
# downloaded OF directory. If OF is reinstalled, you may need to
# re-run the previous step.

# Finally, re-run loopin-native with a simple test program.  
loopin-native -T

# If everything goes well, you should see a window with the
# text 'Loopin Lives!'
```

## Raspberry PI

*Currently testing with Raspbian Jessie Lite on both Pi 1 & Pi 3*

The procedure for installation on generic Linux should work. A few PI-specific notes:

* Use [raspbian lite](https://www.raspberrypi.org/downloads/raspbian/) image.
* Don't install desktop!
* Installer currently forces armv6 architecture.
* Installation and compiling can take *hours*, even on a PI 3. Deploy early and often!
* GL ES shader support still needs a lot of work.

## Windows

Sorry, at this point there is no support for Windows. Although running on Windows should be a matter of some additional configuration, documentation and maybe hammering out some path delimiter issues, I have neither the resources or the desire to do it at this time. *Frankly, I kind of hate Windows.*

If you would like to help getting Loopin running on Windows, please contact me and we'll figure it out.

# Build Process

Internally, the file `src/builder.js` implements the following procedure:

* Download the latest [openFrameworks](http://openframeworks.cc) release. OF is installed
into unpacked into `~/_loopin/native/openFrameworks/{version}`.
* Use `git` to download the following addons into the addons folder of the OF installation.
  * [ofxJSON](https://github.com/jefftimesten/ofxJSON)
  * [ofxSyphon](https://github.com/astellato/ofxSyphon) ( mac only )
  * [ofxTrueTypeFontUC](https://github.com/hironishihara/ofxTrueTypeFontUC) ( experimental )
* Creates a new openFrameworks project named 'Loopin', using openFrameworks' project generator. The project is stored in `~/_loopin/native/0.7/Loopin`.
* Overwrite `main.cpp` and add some default files.
* Compile the binary using `make`.
* Optionally run the binary and return the process.
