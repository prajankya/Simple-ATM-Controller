#
# Set minimum required version
cmake_minimum_required(VERSION 3.11)


############## Setup Project ##############

#
# Project version
set(MAJOR_VERSION 0)
set(MINOR_VERSION 1)
set(PATCH_VERSION 0)

set(VERSION_STRING ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})

project(ATM_Controller LANGUAGES CXX)

message(STATUS "Building Simple ATM Controller: ${VERSION_STRING}")

#
# Defaults to Build Release
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

#
# Set C++ Version 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++17 -O3")

#
# Deactivate RPATH for MacOSX
set(CMAKE_MACOSX_RPATH 0)

#
# add path where cmake files must be searched for
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)


add_subdirectory(src)


############## Setup Dependencies ##############

# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)
# FetchContent_MakeAvailable was not added until CMake 3.14; use our shim
if(${CMAKE_VERSION} VERSION_LESS 3.14)
  include(cmake/add_FetchContent_MakeAvailable.cmake)
endif()


############## Tests ##############

option(PACKAGE_TESTS "Build the tests" OFF)

string(TOUPPER "${CMAKE_BUILD_TYPE}" uppercase_CMAKE_BUILD_TYPE)

if (uppercase_CMAKE_BUILD_TYPE STREQUAL "DEBUG")
  set(IS_DEBUG_MODE True)
endif()

if (IS_DEBUG_MODE)
  message(STATUS "======= Building all tests ========")
  set(PACKAGE_TESTS ON)
endif(IS_DEBUG_MODE)

if(PACKAGE_TESTS)
  enable_testing()

  set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
  set(BUILD_GTEST ON CACHE BOOL "" FORCE)

  # Add Google test suite
  FetchContent_Declare(googletest
      GIT_REPOSITORY      https://github.com/google/googletest.git
      GIT_TAG             release-1.10.0)
  FetchContent_MakeAvailable(googletest)

  # add_subdirectory(tests)
endif(PACKAGE_TESTS)


############## Documentation ##############

option(BUILD_DOC "Build documentation" ON)

if (BUILD_DOC)
  # check if Doxygen is installed
  find_package(Doxygen)
  if (DOXYGEN_FOUND)
      message(STATUS "======= Building Documentation ========")

      # set input and output files
      set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Doxyfile.cmake.in)
      set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
      configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

      # note the option ALL which allows to build the docs together with the application
      add_custom_target( doc_doxygen ALL
          COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
          COMMENT "Generating API documentation with Doxygen"
          VERBATIM )
  else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
  endif (DOXYGEN_FOUND)
endif(BUILD_DOC)
