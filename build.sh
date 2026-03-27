#!/bin/bash

CC=g++
CPPFLAGS=`pkg-config --cflags glew ImageMagick++`
OGL_CPPFLAGS="$CPPFLAGS -I./include -std=c++23"
OGL_LDFLAGS=`pkg-config --libs glew ImageMagick++ glut`
FILES_2_COMPILE="./common/ogldev_util.cpp ./common/pipeline.cpp ./common/math_3d.cpp ./common/camera.cpp ./common/ogldev_atb.cpp ./common/glut_backend.cpp ./common/ogldev_texture.cpp ./common/3rdparty/stb_image.cpp"

$CC main.cpp $FILES_2_COMPILE $OGL_CPPFLAGS $OGL_LDFLAGS -o main
