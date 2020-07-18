#!/bin/bash

#assuming starts at scripts folder
echo "installing dependencies:"
sudo apt-get update

echo "installing xorg-dev"
sudo apt-get install xorg-dev

echo "installing libsound2"
sudo apt-get install libasound2-dev

#remove build folder
cd ..
rm -r -f Build/

./Premake_bin/Linux/premake5 gmake
echo "Premake configured"

cd Build

echo "Starting compilation"
make -j4 config=release



