**loopin-native** contains all that is needed to run [Loopin](https://github.com/koopero/loopin)
applications using a share, natively compiled binary. It includes the following:

* C++/[openFrameworks](http://openframeworks.cc) source code for the reference Loopin server implementation (ofxLoopin)
* node.js functions to automatically build and run the The Binary.  *src/\*)
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
cd ~/_loopin/native/lib/openframeworks/scripts/linux/ubuntu

# openframeworks scripts to auto-install dependencies
# You will need to hit 'Y' a number of times.
sudo ./install_dependencies.sh
sudo ./install_codecs.sh

# Finally, re-run loopin-native with a simple test program.  
loopin-native -T

# If everything goes well, you should see a window with the
# text 'Loopin Lives!'
```


## Windows

Sorry, at this point there is no support for Windows. Although running on Windows should be a matter of some additional configuration, documentation and maybe hammering out some path delimiter issues, I have neither the resources or the desire to do it at this time. *Frankly, I kind of hate Windows.*

If you would like to help getting Loopin running on Windows, please contact me and we'll figure it out.

# Build Process

Internally, the file `src/builder.js` implements the following procedure:

* Download the latest [openFrameworks](http://openframeworks.cc) release.
* Use `git` to download the following addons.
  * [ofxJSON](https://github.com/jefftimesten/ofxJSON)
  * [ofxSyphon](https://github.com/astellato/ofxSyphon)
  * [ofxTrueTypeFontUC](https://github.com/hironishihara/ofxTrueTypeFontUC)
* Creates a new openFrameworks project named 'Loopin', using openFrameworks' project generator.
* Overwrite `main.cpp` and add some default files.
* Compile the binary using `make`.
* Optionally run the binary and return the process.

Currently, the root for all builds is `~/_loopin`.
