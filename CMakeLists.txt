cmake_minimum_required(VERSION 3.30)
project(quasar CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)


add_executable(quasar
        quasar/main.cpp
)

target_link_libraries(quasar PRIVATE mimalloc zstd)