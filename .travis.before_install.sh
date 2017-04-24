#! /usr/bin/env bash
#
# copyright (c) 2015 Zhang Rui <bbcallen@gmail.com>
#
# This file is part of jni4android.
#
# jni4android is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# jni4android is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with jni4android; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
#/

echo ".travis.before_install: $TRAVIS_OS_NAME"
case "$TRAVIS_OS_NAME" in
    osx)
        brew update
        brew outdated flex || brew upgrade flex
        # bison in homebrew is too old
        # brew outdated bison || brew upgrade bison
    ;;
esac
