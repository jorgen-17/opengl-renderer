#!/bin/bash

CC=g++
CPPFLAGS=`pkg-config --cflags glew ImageMagick++ freetype2`
OGL_CPPFLAGS="$CPPFLAGS -I./include -I./include/assimp5 -I./include/gl -I./common/FreetypeGL -I./common/3rdparty/meshoptimizer/src -std=c++23"
OGL_LDFLAGS=`pkg-config --libs glew ImageMagick++ freetype2 assimp`

ADD_LD_FLAGS=""
OS=$(uname -s) # -s option provides the system name
case "$OS" in
    Linux)
        echo "Running on Linux"
        ADD_LD_FLAGS="-lglfw -lmeshoptimizer"
        ;;
    Darwin)
        echo "Running on macOS"
        ADD_LD_FLAGS="-L/opt/homebrew/lib -lglew -lassimp -lglfw ./common/3rdparty/meshoptimizer/build/libmeshoptimizer.a -framework Cocoa -framework OpenGL -framework IOKit -framework QuartzCore"
        ;;
    *)
        echo "Unknown OS: $OS"
        ;;
esac

OGL_LDFLAGS="$OGL_LDFLAGS $ADD_LD_FLAGS"
FILES_2_COMPILE="picking_technique.cpp picking_texture.cpp simple_color_technique.cpp ./common/3rdparty/stb_image.cpp ./common/FreetypeGL/freetypeGL.cpp ./common/camera.cpp ./common/math_3d.cpp ./common/pipeline.cpp ./common/technique.cpp ./common/ogldev_app.cpp ./common/ogldev_atb.cpp ./common/ogldev_basic_glfw_camera.cpp ./common/ogldev_basic_lighting.cpp ./common/ogldev_basic_mesh.cpp ./common/ogldev_glfw.cpp ./common/ogldev_glfw_camera_handler.cpp ./common/ogldev_glm_camera.cpp ./common/ogldev_new_lighting.cpp ./common/ogldev_shadow_map_fbo.cpp ./common/ogldev_texture.cpp ./common/ogldev_util.cpp ./common/ogldev_world_transform.cpp"

compile="$CC -g main.cpp $FILES_2_COMPILE $OGL_CPPFLAGS $OGL_LDFLAGS -o main"
echo $compile
$compile
