consolidating [olgdev](https://github.com/emeiri/ogldev) tutorials

using [bear](https://github.com/rizsotto/Bear) tool to generate compile_commands.json so that clangd can find function definitions in the cpp files not just the declarations in the .h files
```bash
sudo apt install bear
bear -- ./build.sh
```
