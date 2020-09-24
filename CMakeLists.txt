project(reitrace)
cmake_minimum_required(VERSION 3.14)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

add_compile_options(-std=c++20 -Wall -Wextra)
add_compile_options(-Wpedantic -Wfatal-errors)
add_compile_options(-g -ggdb -O3)
add_compile_options(-lm -Ilib -Iinclude)
add_compile_options(-v)

add_executable(render src/render.cpp)

add_custom_target(hw1_groeling.tar ALL COMMAND tar cf hw1_groeling.tar src include lib CMakeLists.txt)
