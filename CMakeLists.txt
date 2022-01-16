cmake_minimum_required(VERSION 2.8)
project(VDSProject CXX C)
include(ExternalProject)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC -std=c++11 ${LLVM_CXX_FLAGS} ")

#Include dirs
include_directories(${CMAKE_SOURCE_DIR}/src)
link_directories(${CMAKE_SOURCE_DIR}/src)

include_directories(${CMAKE_SOURCE_DIR}/src/test/)
link_directories(${CMAKE_SOURCE_DIR}/src/test/)

ExternalProject_Add(GTEST
        # Location for external project with standard folder structure. Distinct by version
        PREFIX ${CMAKE_SOURCE_DIR}/src/test/googletest/1.11.0
        # Download the project from git via versioned tag. Checkout only the tag. Be verbose.
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
        GIT_PROGRESS TRUE

        # Do not update the project, as we intentionally checked out a specific version.
        UPDATE_COMMAND ""

        # Install locally in the project
        CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_SOURCE_DIR}

        INSTALL_COMMAND make install

        )

ExternalProject_Add_Step(GTEST FORCED_INSTALL
        DEPENDERS install
        COMMAND ${CMAKE_COMMAND} -E echo "Installing GTEST-${GTEST_VERSION}"
        COMMENT "Installing GTEST-${GTEST_VERSION}"
        ALWAYS TRUE
        )
set(GTEST_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
include_directories(${GTEST_INCLUDE_DIR})

set(GTEST_LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
find_library(gtest gtest ${GTEST_LIB_DIR})
link_directories(${GTEST_LIB_DIR})

add_subdirectory(src)
add_executable(VDSProject src/main.cpp)
target_link_libraries(VDSProject Manager ${GTEST_LIB_DIR}/libgtest.a)
