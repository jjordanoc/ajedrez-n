set(BINARY ${CMAKE_PROJECT_NAME})

# SFML
set(SFML_ROOT "../lib/SFML")
set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS graphics audio REQUIRED)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true backend/*.h backend/*.cpp frontend/*.h frontend/*.cpp global/*.h main.cpp)
file(GLOB_RECURSE SOURCES_BACKEND LIST_DIRECTORIES true backend/*.h backend/*.cpp)

set(SOURCES ${SOURCES} ${SOURCES_BACKEND} frontend/states/Rules.cpp frontend/states/Rules.h)

add_executable(${BINARY} ${SOURCES})

target_link_libraries(${BINARY} sfml-graphics sfml-audio sfml-window sfml-system)

add_library(${BINARY}_lib STATIC ${SOURCES_BACKEND} )

target_link_libraries(${BINARY}_lib sfml-graphics sfml-audio sfml-window sfml-system)
