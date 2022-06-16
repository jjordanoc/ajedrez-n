cmake_minimum_required(VERSION 3.22)
project(proyecto)

set(CMAKE_CXX_STANDARD 23)

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/GoogleTest)
add_subdirectory(lib/SFML)

#set(SFML_STATIC_LIBRARIES TRUE)
#set(SFML_DIR lib/SFML/cmake)

# find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

target_link_libraries(proyecto sfml-window sfml-graphics sfml-audio)