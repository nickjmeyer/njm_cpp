## Setup external libraries as interface libraries
add_library(njm_cpp_boost INTERFACE)
find_package(Boost REQUIRED thread system filesystem)
target_link_libraries(njm_cpp_boost INTERFACE ${Boost_LIBRARIES})
target_include_directories(njm_cpp_boost INTERFACE ${Boost_INCLUDE_DIR})

add_library(njm_cpp_gsl INTERFACE)
find_package(GSL REQUIRED)
target_link_libraries(njm_cpp_gsl INTERFACE ${GSL_LIBRARIES})
target_include_directories(njm_cpp_gsl INTERFACE ${GSL_INCLUDE_DIRS})

add_library(njm_cpp_glog INTERFACE)
find_package(Glog REQUIRED)
target_link_libraries(njm_cpp_glog INTERFACE ${GLOG_LIBRARIES})
target_include_directories(njm_cpp_glog INTERFACE ${GLOG_INCLUDE_DIRS})

add_library(njm_cpp_blas INTERFACE)
find_package(OpenBLAS)
if(${OpenBLAS_FOUND})
  target_link_libraries(njm_cpp_blas INTERFACE ${OpenBLAS_LIB})
  target_include_directories(njm_cpp_blas INTERFACE ${OpenBLAS_INCLUDE_DIR})
  MESSAGE(${OpenBLAS_INCLUDE_DIR})
else()
  find_package(BLAS)
  if (NOT ${OpenBLAS_FOUND})
    MESSAGE(FATAL_ERROR "BLAS is necessary.  If on OSX 'brew install openblas'."
      "  If on Ubuntu 'sudo apt install libopenblas-dev'.")
  endif()
  target_link_libraries(njm_cpp_blas INTERFACE ${BLAS_LIBRARIES})
endif()


## git revision control for project info
include(GetGitRevisionDescription)
git_describe(GIT_SHA1_VAR)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/info/project.cpp.in"
  "${CMAKE_CURRENT_BINARY_DIR}/src/info/project.cpp" @ONLY)


set(NJM_CPP_SRCS
  ## data
  src/data/trapperKeeper.cpp

  ## info
  ${CMAKE_CURRENT_BINARY_DIR}/src/info/project.cpp

  ## linalg
  src/linalg/stdVectorAlgebra.cpp

  ## optim
  src/optim/optim.cpp
  src/optim/simPerturb.cpp

  ## thread

  ## tools
  src/tools/bitManip.cpp
  src/tools/random.cpp
  src/tools/stats.cpp)



add_library(njm_cpp ${NJM_CPP_SRCS})
MESSAGE("${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(njm_cpp PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(njm_cpp PRIVATE njm_cpp_boost njm_cpp_gsl njm_cpp_glog
  njm_cpp_blas)


if(${NJM_CPP_BUILD_TESTS})
  set(NJM_CPP_TEST_SRCS
    ## data
    test_trapperKeeper.cpp

    ## linalg
    test_stdVectorAlgebra.cpp

    ## optim
    test_simPerturb.cpp

    ## thread
    test_pool.cpp

    ## tools
    test_bitManip.cpp
    test_experiment.cpp
    test_progress.cpp
    test_stats.cpp)

  foreach(test_src ${NJM_CPP_TEST_SRCS})
    get_filename_component(test_bin ${test_src} NAME_WE)
    add_executable(${test_bin} test_src)
    target_link_libraries(${test_bin} njm_cpp gtest)
    add_test(${test_bin} ${test_bin})
  endforeach(test_src)

endif()
