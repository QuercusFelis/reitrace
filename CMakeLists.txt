project(reitrace)

cmake_minimum_required(VERSION 3.14)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

add_compile_options(-std=c++17 -Wall -Wextra)
add_compile_options(-Wpedantic -Wfatal-errors)
#add_compile_options(-g -ggdb -O0)
add_compile_options(-O3)
add_compile_options(-lm -Ilib -Iinclude)
add_compile_options(-v)

add_executable(raytracer src/hw4.cpp)

add_custom_target(hw4_groeling.tar ALL COMMAND tar cf hw4_groeling.tar src include lib CMakeLists.txt README.md)
