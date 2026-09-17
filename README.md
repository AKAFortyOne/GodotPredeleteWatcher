### 如何编译
```commandline
git clone https://github.com/AKAFortyOne/GodotDeathWatcher
git submodule update --init --recursive
```

Debug编译dll：`scons platform=windows arch=x86_64 target=template_debug debug_symbols=yes dev_build=yes use_static_cpp=yes compiledb=yes`

Release编译dll：`scons platform=windows arch=x86_64 target=template_release debug_symbols=no dev_build=no use_static_cpp=yes compiledb=yes`

更新IDE的自动补全：`scons platform=windows arch=x86_64 target=template_debug debug_symbols=yes dev_build=yes use_static_cpp=yes compiledb`