#!/bin/bash

if [ -z "$1" ]; then
  echo "Please choose build type: G or C"
  exit
else 
  if [ "$1" == "G" ]; then
    COMPILERS="-DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc"
  else
    if [ "$1" == "C" ]; then
      COMPILERS="-DCMAKE_CXX_COMPILER=c++ -DCMAKE_C_COMPILER=cc"
    else
      echo "Please choose build type: G or C"
      exit
    fi
  fi
fi

if [ "$2" == "WIDE" ]; then
  IS_WIDE=ON
else
  IS_WIDE=OFF
fi
mkdir build_$1
pushd build_$1 && cmake -DCMAKE_BUILD_TYPE=Debug -DIS_WIDE=$IS_WIDE -G "Unix Makefiles" $COMPILERS .. && make TestEncoding && ./TestEncoding
popd 
