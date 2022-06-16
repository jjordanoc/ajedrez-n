cmake_minimum_required(VERSION 3.22)
project(proyecto)

set(CMAKE_CXX_STANDARD 23)

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/GoogleTest)

set(SOURCES ${SOURCES})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true src/backend/*.h src/backend/*.cpp src/frontend/*.h src/frontend/*.cpp)

add_executable(proyecto src/main.cpp ${SOURCES})

add_library(libraries STATIC ${SOURCES})

set(SFML_ROOT "lib/SFML")
set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML COMPONENTS graphics audio REQUIRED)

target_link_libraries(proyecto sfml-graphics sfml-audio sfml-window sfml-system)