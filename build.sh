#!/bin/bash

if [ -z "$1" ] then
  echo "Please choose build type"
  exit 1
fi

if [ "$2" == "WIDE" ] then
  IS_WIDE=ON
else
  IS_WIDE=OFF
fi
mkdir build
pushd build && cmake -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" .. && make TestEncoding && ./TestEncoding
popd build