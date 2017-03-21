cmake_minimum_required(VERSION 3.1)
project(njm_cpp CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

## add modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

## A flag to determine if tests are being built.  It can be enabled
## for a few different reasons.  This should not be manually set.  If
## you want to manually build tests, use the option
## NJM_CPP_FORCE_BUILD_TEST.
set(NJM_CPP_BUILD_TESTS NO)

## check if njm_cpp is the root project or if its being included in
## another project
if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
  set(NJM_CPP_IS_ROOT_PROJECT YES)
else()
  set(NJM_CPP_IS_ROOT_PROJECT NO)
endif()

## check for a force build for tests
if(DEFINED NJM_CPP_FORCE_BUILD_TEST)
else()
  set(NJM_CPP_FORCE_BUILD_TEST YES)
endif()

## Setup testing (set NJM_CPP_FORCE_BUILD_TEST to always build tests)
if(${NJM_CPP_IS_ROOT_PROJECT} OR ${NJM_CPP_FORCE_BUILD_TEST})
  enable_testing()
  set(NJM_CPP_BUILD_TESTS YES)
  MESSAGE("Building tests for njm_cpp.")

  if(NOT TARGET gtest) ## check if the target already exists
    add_subdirectory(libs/googletest)
  endif()
else()
  MESSAGE("Skipping tests for njm_cpp.")
endif()

## build library
add_subdirectory(njm_cpp)
