#!/bin/bash

CC=g++
CPPFLAGS=`pkg-config --cflags glew ImageMagick++ freetype2`
OGL_CPPFLAGS="$CPPFLAGS -I./include -I./common/FreetypeGL -std=c++23"
OGL_LDFLAGS=`pkg-config --libs glew ImageMagick++ freetype2 assimp`
OGL_LDFLAGS="$OGL_LDFLAGS -lglfw -lmeshoptimizer"
FILES_2_COMPILE="./common/3rdparty/stb_image.cpp ./common/FreetypeGL/freetypeGL.cpp ./common/camera.cpp ./common/math_3d.cpp ./common/pipeline.cpp ./common/technique.cpp ./common/ogldev_app.cpp ./common/ogldev_atb.cpp ./common/ogldev_basic_glfw_camera.cpp ./common/ogldev_basic_lighting.cpp ./common/ogldev_basic_mesh.cpp ./common/ogldev_framebuffer.cpp ./common/ogldev_glfw.cpp ./common/ogldev_glfw_camera_handler.cpp ./common/ogldev_glm_camera.cpp ./common/ogldev_new_lighting.cpp ./common/ogldev_shadow_map_fbo.cpp ./common/ogldev_shadow_mapping_technique.cpp ./common/ogldev_texture.cpp ./common/ogldev_util.cpp ./common/ogldev_world_transform.cpp"

$CC -g main.cpp $FILES_2_COMPILE $OGL_CPPFLAGS $OGL_LDFLAGS -o main
