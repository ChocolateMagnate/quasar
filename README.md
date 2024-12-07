# Quasar
Quasar project aims to be a JIT compiler for Python programming language focusing on 
performance, compatibility and use of use.

# Building from source
1. Install dependencies
2. Make a build directory
3. Generate Makefile
4. Build
```shell
# RHEL/Fedora
dnf install libcxx libcxx-devel clang-tools-extra mimalloc libzstd mimalloc-devel libzstd-devel
mkdir build && cd build
cmake ..
make -j$(nproc)
```