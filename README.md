consolidating [olgdev](https://github.com/emeiri/ogldev) tutorials

using [bear](https://github.com/rizsotto/Bear) tool to generate compile_commands.json so that clangd can find function definitions in the cpp files not just the declarations in the .h files
```bash
sudo apt install bear
bear -- ./build.sh
```

features I'd like to add:
1. select object to scale, translate, and rotate them
2. menu to add objects into scene (dear imgui)
3. support various camera objects in scene and switching between them
4. add basic models for lights:
    a. spot light cones
    b. point light cubes that glow
5. save and load scenes
6. grid
7. blender materials
8. cell shading
