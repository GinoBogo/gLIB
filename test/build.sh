#!/usr/bin/env bash

clear

path=$(
    cd "$(dirname "$0")"
    pwd -P
)

rm -rf $path/build 2>/dev/null
mkdir $path/build
cd $path/build

#echo "PWD:" $PWD

if [ $# = 0 ]; then
    cmake $path -G "Ninja" -DCMAKE_BUILD_TYPE=release
else
    cmake $path -G "Ninja" -DCMAKE_BUILD_TYPE=$1
fi

ninja
