#!/bin/bash

current_dir=$(pwd)
echo $current_dir

# pull down meshoptimizer source
git submodule update --init

# macos comes with clang which uses g++ as an alias so not installing g++ via brew
brew install pkgconfig make cmake glew glfw assimp

# compile libmeshoptimizer.a in meshoptimizer/build
cd ./common/3rdparty/meshoptimizer/
mkdir build && cd build
cmake ../CMakeLists.txt
make

# go back to original dir used when executed this script
cd $current_dir

cd ./common/3rdparty/glfw/
mkdir build && cd build
cmake ../CMakeLists.txt
make

# go back to original dir used when executed this script
cd $current_dir

 # libs to include later on in the proj: libmagick++-dev vulkan-tools vulkan-validationlayers vulkan-utility-libraries-dev glslang-dev glslang-tools
