cmake_minimum_required(VERSION 3.8)
project(VSClient)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.c)

link_libraries(ws2_32.lib)
add_executable(VSClient ${SOURCE_FILES})