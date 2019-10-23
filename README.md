**loopin-native** contains all that is needed to run [Loopin](https://github.com/koopero/loopin)
applications using a shared, natively compiled binary: `ofxLoopin`. It includes the following:

* C++/[openFrameworks](http://openframeworks.cc) source code for the reference Loopin server implementation `ofxLoopin`.
* A [loopin](https://github.com/koopero/loopin) plugin to interface with the rest of the Loopin stack.
* node.js functions to automatically build `ofxLoopin`.  *src/\**
* Command-line utility `loopin-native` to manage, build and run `ofxLoopin`. *src/cli.js*  

**To create a Loopin project, use the [loopin-base](https://github.com/koopero/loopin-base) module. You should not need to include in module directly.**

# Usage

This module must be used as part of a loopin application. For a much more complete example, see [loopin-base/node/loopin.js](https://github.com/koopero/loopin-base/blob/master/node/loopin.js).
``` js
const loopin = require('loopin').global()

// Set project root
loopin.plugin('files')
loopin.filesRoot( __dirname )

// Snip a lot of other loopin configuration.

// Load loopin-native as a plugin
loopin.plugin( require('loopin-native'), {
  dev: false,
  useEnv: true
} )

// Start loopin application.
loopin.bootstrap()
.then( function () {
  // Loopin is successfully booted!
})
```

This will download a pre-compiled binary version of ofxLoopin under `./node_modules/loopin-native/build/` and run it with the loopin project.

# Requirements

**loopin-native** runs best on a 64-bit Mac **OSX** machine.

**Linux**, at least ubuntu-amd64, is supported but will need to be build in **developer mode**.

**Raspberry Pi** is supported, with specific instructions and **developer mode**. Some features, such as Kinect, are not enabled. Shaders must be written in OpenGL ES.

**Windows** support is very new, and may have some weirdness.

# Installation

## OSX / Windows

Running and installation should be automatic on OSX 10.8 and above and modern versions of Windows. Compiled binaries will be downloaded from github.

## Linux

Installations on linux will probably need to install openframeworks dependencies.

### 'Automatic' Linux Deps Install 

``` sh
# Install the loopin-native module
sudo npm install -g loopin-native

# Attempt to auto-run dependency installers. 
# Downstream scripts will pop up Y/n prompts.
# Y is not always the correct answer! 
sudo loopin-native --deps 

```

### Manual Linux Deps Install
``` sh
# Install prerequisites using apt-get. This may be yum or dnf on your machine.
sudo apt-get install build-essential git nodejs npm ffmpeg

# Install the loopin-native module
sudo npm install -g loopin-native

# Setup dev environment.
# This will download openFrameworks.
`loopin-native --dev --env`

# Change to loopin-native module directory.
cd "$LOOPIN_NATIVE_ROOT"

# Change to openFrameworks directory
cd lib/of_*

# Change to scripts directory.
# You may need to replace 'ubuntu' with your distribution.
cd scripts/linux/ubuntu/

# openframeworks scripts to auto-install dependencies
# You will need to hit 'Y' a number of times.
sudo ./install_dependencies.sh
sudo ./install_codecs.sh
```

After this, Loopin applications, whether using pre-compiled binaries or in dev mode, *should* work. Please report any problems.

## Raspberry PI

The procedure for installation on generic Linux should work. A few PI-specific notes:

* Use [Raspbian Stretch Lite](http://ftp.ubuntu-tw.org/mirror/raspbian-downloads/raspbian_lite/images/raspbian_lite-2019-04-09/) image. *Raspbian Buster has changed packages, making it incompatible with openframeworks 0.10.1.*
* Don't install desktop!
* Installer currently forces armv6 architecture.
* For compatibility reasons, binaries are not distributed for Raspberry PI, so developer mode is forced.
* Installation and compiling can take *hours*, even on a PI 3. Deploy early and often! See 'Setting up environment' to use only one copy of `loopin-native`.

## Developer Mode

`loopin-native` is capable of setting up a development environment and building `ofxLoopin` binaries in-situ and on-demand. This can be used for `ofxLoopin` feature development as well as building on platforms that are currently unsupported. Developer mode is automatically enabled on platforms where a pre-packaged binary is not distributed, including Linux. Note that developer mode may automatically download and install libraries and dependencies, totalling more than 100mb.

``` sh
# Compile ofxLoopin and do a simple test.
loopin-native --dev --verbose --test
```

### Requirements

[XCode](https://developer.apple.com/xcode/) is required on Mac. **XCode 10.x.x and 9.x.x must be used. XCode 11 is currently unsupported. Turn auto-update off!**

[Visual Studio Community 2017](https://visualstudio.microsoft.com/vs/community/) is required on Windows. 

## Potential Troubles

openFrameworks build processes may not work when the installation of this module is in any directory who's path includes dotfiles. Specifically, this can be problem when using **nvm**. To mitigate this problem, use the instructions below and ensure that the module is installed globally in a path that doesn't have any dotfiles. 

## Setting up shared environment

When developing `ofxLoopin` or running multiple Loopin projects, it is recommendeded to use a single, shared copy of this module.

``` sh
cd WHERE_YOU_PUT_YOUR_CODE/

# Clone this repo
git clone https://github.com/koopero/loopin-native.git

# Install npm deps
cd loopin-native
npm install

# Link module globally.
sudo link npm link

# Show environment variables
loopin-native --dev --env
```

The output of the last command will look something like this:

``` sh
export LOOPIN_NATIVE_ROOT=/your/dir/loopin-native/build
export LOOPIN_NATIVE_DEV=1
```

Copy this output and paste it into a file which is run on login, such as `~/.bashrc` or `/etc/environment`.

Now, all local project which `require('loopin-native')` will default to using the directory `./loopin-native/build`, and will build binaries on demand. You can now edit files in `./loopin-native/ofxLoopin` to experiment with or develop **ofxLoopin**.


# Credits

[Loopin](https://github.com/koopero/loopin) is created by Vancouver-based creative technologist [Samm Zuest Cooper](https://github.com/koopero).

Loopin development relies on the patient and enthusiastic support of [HFour Design Studio](http://hfour.ca/).

`ofxLoopin` would not be possible without the incredible [openFrameworks](http://openframeworks.cc/community/) project.


Thank you to the wonderful organizers and community at [Vancouver Creative Technology](https://www.meetup.com/Vancouver-Creative-Technology/) for feedback and encouragement.

The following, amazing [ofxAddons](http://www.ofxaddons.com/) help make Loopin great:

- [ofxSyphon](https://github.com/astellato/ofxSyphon) by [astrello](https://github.com/astellato).
