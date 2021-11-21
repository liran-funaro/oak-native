#!/bin/bash

mkdir -p cmake-build-release
cd cmake-build-release || exit 1
rm -rf ./*
scl enable devtoolset-9 "cmake -DCMAKE_BUILD_TYPE=Release .."
cmake --build .
