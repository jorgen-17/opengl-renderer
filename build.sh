#!/bin/bash

CC=g++
OGL_CPPFLAGS="$CPPFLAGS -I./include -std=c++20"
GLEW_LDFLAGS=`pkg-config --libs glew`
GLUT_LDFLAGS=`pkg-config --libs glut`
OGL_LDFLAGS="$GLEW_LDFLAGS $GLUT_LDFLAGS"
FILES_2_COMPILE="./common/ogldev_util.cpp ./common/pipeline.cpp ./common/math_3d.cpp ./common/camera.cpp ./common/ogldev_atb.cpp"

$CC main.cpp $FILES_2_COMPILE $OGL_CPPFLAGS $OGL_LDFLAGS -o main
