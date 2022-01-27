cmake_minimum_required(VERSION 2.8)
project(VDSProject CXX C)
include(ExternalProject)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC -std=c++11 ${LLVM_CXX_FLAGS} ")

#Include dirs
include_directories(${CMAKE_SOURCE_DIR}/src)
link_directories(${CMAKE_SOURCE_DIR}/src)

include_directories(${CMAKE_SOURCE_DIR}/src/test/)
link_directories(${CMAKE_SOURCE_DIR}/src/test/)

include_directories(${CMAKE_SOURCE_DIR}/src/bench/)
link_directories(${CMAKE_SOURCE_DIR}/src/bench/)

include_directories(${CMAKE_SOURCE_DIR}/src/verify/)
link_directories(${CMAKE_SOURCE_DIR}/src/verify/)

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



set(BOOST_URL https://boostorg.jfrog.io/artifactory/main/release/1.76.0/source/boost_1_76_0.tar.gz)
set(BOOST_HASH 4f0bef9781c53900fbc413fec1058918c7a546aa023eeda7b3270bc9d2289ec1ba4be734895ded86109789d6da23dc0f1f00b7d6a0ee871d6853cc1fc52546bb)

set(BOOST_SRC_DIR "${CMAKE_SOURCE_DIR}/BOOST/src/BOOST")
set(BOOST_PACKAGES "system,filesystem")

set(BOOST_LIBS libboost_filesystem.so;libboost_system.so)


#REMEMBER: In each library, that is using JSON: do following: #include <boost/json/src.hpp>
#TODO Build a shared library for boost::json only including and building <boost/json/src.hpp>

ExternalProject_Add(BOOST
        PREFIX ${CMAKE_SOURCE_DIR}/BOOST
        URL ${BOOST_URL}
        URL_HASH SHA512=${BOOST_HASH}
        CONFIGURE_COMMAND ""
        BUILD_COMMAND cd ${BOOST_SRC_DIR} && ./bootstrap.sh --prefix=./ --with-libraries=${BOOST_PACKAGES}
        INSTALL_COMMAND cd ${BOOST_SRC_DIR} && ./b2
        )

set(BOOST_INCLUDE_DIR ${BOOST_SRC_DIR})
set(BOOST_LIB_DIR ${BOOST_SRC_DIR}/stage/lib)
include_directories(${BOOST_INCLUDE_DIR})

find_library(BOOST BOOST ${BOOST_LIB_DIR})
link_directories(${BOOST_LIB_DIR})

add_subdirectory(src)


add_executable(VDSProject src/main.cpp)
target_link_libraries(VDSProject Manager ${GTEST_LIB_DIR}/libgtest.a)
