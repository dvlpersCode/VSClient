cmake_minimum_required(VERSION 3.8)
project(VSClient)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.c src/ClientInput.c src/ClientInput.h src/StringUtillities.c src/StringUtillities.h src/main.h)

link_libraries(ws2_32.lib)
add_executable(VSClient ${SOURCE_FILES} src/ClientInput.c src/ClientInput.h src/StringUtillities.c src/StringUtillities.h)