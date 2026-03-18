#!/bin/bash

# if ROOTDIR is unset, then set it to .
if [ -v $ROOTDIR ]; then
    ROOTDIR="."
   fi

CC=g++
OGL_CPPFLAGS="$CPPFLAGS -I$ROOTDIR/include -std=c++20"
GLEW_LDFLAGS=`pkg-config --libs glew`
GLUT_LDFLAGS=`pkg-config --libs glut`
OGL_LDFLAGS="$GLEW_LDFLAGS $GLUT_LDFLAGS"

$CC main.cpp $ROOTDIR/common/ogldev_util.cpp $ROOTDIR/common/pipeline.cpp $ROOTDIR/common/math_3d.cpp $OGL_CPPFLAGS $OGL_LDFLAGS -o main
