cmake_minimum_required(VERSION 3.0)
project(timer)

include(ExternalProject)
ExternalProject_Add(list
        GIT_REPOSITORY https://github.com/fsodari/list.git
        #SOURCE_DIR "${CMAKE_BINARY_DIR}/list-src"
        #BINARY_DIR "${CMAKE_BINARY_DIR}/list-build"
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/list-install
        )

add_subdirectory(src)
add_subdirectory(tests)
