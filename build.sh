#!/bin/bash

# if ROOTDIR is unset, then set it to .
if [ -v $ROOTDIR ]; then
    ROOTDIR="."
   fi

CC=g++
OGL_CPPFLAGS="$CPPFLAGS -I$ROOTDIR/include -std=c++20"
OGL_LDFLAGS=`pkg-config --libs glew`
OGL_LDFLAGS="$OGL_LDFLAGS -lglut"

$CC main.cpp $ROOTDIR/common/ogldev_util.cpp $OGL_CPPFLAGS $OGL_LDFLAGS -o main
