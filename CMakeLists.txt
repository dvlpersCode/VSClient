cmake_minimum_required(VERSION 3.8)
project(VSClient)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.c)
add_executable(VSClient ${SOURCE_FILES})