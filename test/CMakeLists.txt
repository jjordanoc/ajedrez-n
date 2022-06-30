set(BINARY ${CMAKE_PROJECT_NAME}_test)

# SFML
#set(SFML_ROOT "../lib/SFML")
#set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")
#set(SFML_STATIC_LIBRARIES TRUE)
#find_package(SFML COMPONENTS graphics audio REQUIRED)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)