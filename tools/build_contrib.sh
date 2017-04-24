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

MOD_NAME=$1
MOD_VERSION=$2
MOD_URL=$3
MOD_VERSION_NAME=$MOD_NAME-$MOD_VERSION
MOD_ROOT_DIR=`pwd`

if [ -z $1 -o -z $2 ]; then
    echo "Missing module name or url\"$1\"."
    exit 1
fi

MOD_TARBALL_NAME=$(echo $MOD_URL | sed 's/.*\///' | sed 's/[\?\#].*//')
MOD_TARBALL_DIR=contrib/tarballs
MOD_TARBALL_PATH=$MOD_TARBALL_DIR/$MOD_TARBALL_NAME
MOD_TARBALL_TEMP_PATH=$MOD_TARBALL_DIR/$MOD_TARBALL_NAME.tmp

MOD_BUILD_DIR=contrib/build
MOD_BUILD_SRC_DIR=$MOD_BUILD_DIR/src
MOD_BUILD_SRC_PATH=$MOD_BUILD_SRC_DIR/$MOD_NAME
MOD_BUILD_SRC_PATH=$MOD_BUILD_SRC_DIR/$MOD_NAME
MOD_BUILD_SRC_VERSION_PATH=$MOD_BUILD_SRC_DIR/$MOD_VERSION_NAME

MOD_BUILD_EXTRACT_NAME=$MOD_NAME-$MOD_VERSION
MOD_BUILD_EXTRACT_PATH=$MOD_BUILD_SRC_DIR/$MOD_BUILD_EXTRACT_NAME

########################################
# download and extract
echo " > check contrib $MOD_NAME"
mkdir -p $MOD_TARBALL_DIR
mkdir -p $MOD_BUILD_SRC_DIR

if [ ! -d $MOD_BUILD_SRC_VERSION_PATH ]; then
    if [ ! -f $MOD_TARBALL_PATH ]; then
        echo "download from $MOD_URL"
        wget -O $MOD_TARBALL_TEMP_PATH $MOD_URL
        mv $MOD_TARBALL_TEMP_PATH $MOD_TARBALL_PATH
    fi

    if [ ! -d $MOD_BUILD_SRC_VERSION_PATH ]; then
        echo "extract $MOD_TARBALL_PATH"
        tar -zxvf $MOD_TARBALL_PATH -C $MOD_BUILD_SRC_DIR
    fi

    if [ -h $MOD_BUILD_SRC_PATH ]; then
        rm $MOD_BUILD_SRC_PATH
    fi
fi

if [ ! -h $MOD_BUILD_SRC_PATH ]; then
    echo "link $MOD_BUILD_SRC_VERSION_PATH"
    cd $MOD_BUILD_SRC_DIR
    ln -s $MOD_VERSION_NAME $MOD_NAME
    cd -
fi

########################################
# download and extract
echo " > build contrib $MOD_NAME"

MOD_BUILD_PREFIX=$MOD_ROOT_DIR/$MOD_BUILD_DIR
MOD_BUILD_BIN_DIR=$MOD_ROOT_DIR/$MOD_BUILD_DIR/bin
MOD_BUILD_INC_DIR=$MOD_ROOT_DIR/$MOD_BUILD_DIR/include
MOD_BUILD_LIB_DIR=$MOD_ROOT_DIR/$MOD_BUILD_DIR/lib
MOD_BUILD_OBJ_DIR=$MOD_ROOT_DIR/$MOD_BUILD_DIR/obj

mkdir -p $MOD_BUILD_BIN_DIR
mkdir -p $MOD_BUILD_INC_DIR
mkdir -p $MOD_BUILD_LIB_DIR
mkdir -p $MOD_BUILD_OBJ_DIR

cd $MOD_BUILD_SRC_PATH
./configure --prefix=$MOD_BUILD_PREFIX
make install
cd -
