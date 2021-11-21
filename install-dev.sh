#!/bin/bash

SO_FILE=$(find $(pwd)/cmake-build-release/ -name "lib*.so")
SO_NAME=$(basename ${SO_FILE})
echo "Found lib: ${SO_NAME}"
sudo rm -f SO_FILE
sudo ln -s ${SO_FILE} /usr/local/lib/${SO_NAME}
