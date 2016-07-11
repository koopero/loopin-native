**loopin-native** is a module to wrap the compilation and execution of Loopin's shared native binary. It abstracts platform-specific details and makes building the binary as transparent as possible. The following operations are performed:

* Download the latest [openFrameworks](http://openframeworks.cc) release.
* Use `git` to download [ofxLoopin](https://github.com/koopero/ofxLoopin#README), as well as [ofxJSON](https://github.com/jefftimesten/ofxJSON) and [ofxSyphon](https://github.com/astellato/ofxSyphon).
* Creates a new openFrameworks project named 'Loopin', using openFrameworks' project generator.
* Overwrite `main.cpp` and add some default files.
* Compile the binary using `make`.
* Optionally run the binary and return the process.

Currently, the root for all builds is `~/_loopin`. Although `~/.loopin` would be preferred, the dot seems to give OF's build process some grief.

# Installation

Please remember that since **loopin-native** downloads and compiles a good amount of code, these procedures may take a few minutes.

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

*Tested on Linux Mint 18 Sarah*.

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

# Sister Projects
* [loopin](https://github.com/koopero/loopin#README) - **JS** Hub project.
* [ofxLoopin](https://github.com/koopero/ofxLoopin#README) - **C++** Loopin openframeworks plugin.


# ofxLoopin Development

If you would like to contribute to the development of **ofxLoopin**, or experiment with the source code, you will need to set up your dev environment a bit differently.

``` sh
# ~/PROJECTHOME is the directory where you keep you code.
cd ~/PROJECTHOME

# Clone a fresh copy of the ofxLoopin source
git clone --recursive https://github.com/koopero/ofxLoopin.git ofxLoopin

# Delete the previously downloaded version of the ofxLoopin library
rm -rf ~/_loopin/native/openFrameworks/addons/ofxLoopin/

# Link your copy
ln -s ~/PROJECTHOME/ofxLoopin ~/_loopin/native/openFrameworks/addons/ofxLoopin
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
