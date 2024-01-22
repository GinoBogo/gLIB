#!/usr/bin/env bash

clear

path=$(
    cd "$(dirname "$0")"
    pwd -P
)

rm -rf $path/build 2>/dev/null
