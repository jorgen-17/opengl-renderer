#!/bin/bash

CC=g++
CPPFLAGS=`pkg-config --cflags glew ImageMagick++ freetype2`
OGL_CPPFLAGS="$CPPFLAGS -I./include -I./common/FreetypeGL -std=c++23"
OGL_LDFLAGS=`pkg-config --libs glew ImageMagick++ freetype2 glut assimp`
FILES_2_COMPILE="skinning_technique.cpp skinned_mesh.cpp ./common/ogldev_util.cpp ./common/pipeline.cpp ./common/math_3d.cpp ./common/camera.cpp ./common/ogldev_atb.cpp ./common/glut_backend.cpp ./common/ogldev_texture.cpp ./common/ogldev_basic_lighting.cpp ./common/technique.cpp ./common/ogldev_app.cpp ./common/ogldev_shadow_map_fbo.cpp ./common/FreetypeGL/freetypeGL.cpp ./common/3rdparty/stb_image.cpp ./common/ogldev_world_transform.cpp"

$CC -g main.cpp $FILES_2_COMPILE $OGL_CPPFLAGS $OGL_LDFLAGS -o main
