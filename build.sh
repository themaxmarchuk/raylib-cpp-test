#!/bin/bash

build() {
    echo "Starting build..."
    cmake --build ./build
    echo "Copying executable to source directory..."
    cp build/raylib-cpp-test . -v
}

if [ -d build ] ; then
    build
else
    echo "Generating build files..."
    mkdir build && cd build
    cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=YES
    cd ..
    echo "Linking compile_commands for ccls..."
    ln -sv ./build/compile_commands.json .
    build
fi
