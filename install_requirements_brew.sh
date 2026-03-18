#!/bin/bash

# macos comes with clang which uses g++ as an alias so not installing g++ via brew
# freeglut3-dev -> freeglut
# libglew-dev -> glew
# libglew2.2 -> glew
# need to restart mac if you are installing xquartz for the first time
brew install pkgconfig make freeglut glew xquartz
# libs to include later on in the proj: libmagick++-dev libassimp-dev libglfw3 libglfw3-dev libmeshoptimizer-dev libmeshoptimizer2d vulkan-tools vulkan-validationlayers vulkan-utility-libraries-dev glslang-dev glslang-tools
