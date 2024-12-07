cmake_minimum_required(VERSION 3.30)
project(quasar CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

find_package(absl REQUIRED)

add_executable(quasar
        src/quasar/main.cpp
        include/quasar/Parser.hpp
        include/quasar/Simd.hpp
        include/quasar/Bitcode.hpp
        include/quasar/Iteration.hpp
        src/quasar/Bitcode.cpp
        include/quasar/lib/AbstractSyntaxTree.hpp
)

target_include_directories(quasar PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(quasar PRIVATE mimalloc zstd
        absl::flat_hash_map
        absl::strings)