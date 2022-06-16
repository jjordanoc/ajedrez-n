cmake_minimum_required(VERSION 3.22)
project(proyecto)

set(CMAKE_CXX_STANDARD 23)

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/GoogleTest)

