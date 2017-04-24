# jni4android

[![Build Status](https://travis-ci.org/Bilibili/jni4android.svg?branch=master)](https://travis-ci.org/Bilibili/jni4android)

Generate C wrapper from Pseudo-Java

### My Build Environment
- Common
 - Mac OS X 10.10.5
 - Xcode 7.2 (7C68)
 - flex 2.5.35 Apple(flex-31)
 - bison (GNU Bison) 3.0.4
- [HomeBrew](http://brew.sh)
 - ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
 - brew install git
 - brew install flex
 - brew install bison

### Build

```
git clone https://github.com/Bilibili/jni4android.git jni4android
cd jni4android

# build dependencies
# you don't have to run this if you have bison 3.x installed
./get-deps.sh

./configure
make
```

### Usage

```
Usage:
    j4a -h
    j4a -c [-o <output_file>] <input_file>

Startup:
    -c, --compile         compile file.
    -h, --help            print this help.
    -o, --output          output file.
```

### Example

- input https://github.com/Bilibili/jni4android/blob/master/test/i_java/android/media/AudioTrack.java
- output https://github.com/Bilibili/jni4android/blob/master/test/ref_c/android/media/AudioTrack.h
- output https://github.com/Bilibili/jni4android/blob/master/test/ref_c/android/media/AudioTrack.c
