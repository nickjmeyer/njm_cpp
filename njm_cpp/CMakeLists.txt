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
else()
  find_package(BLAS)
  if (NOT ${BLAS_FOUND})
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
  src/optim/simPerturb.cpp

  ## thread
  src/thread/pool.cpp

  ## tools
  src/tools/bitManip.cpp
  src/tools/experiment.cpp
  src/tools/random.cpp
  src/tools/stats.cpp)



add_library(njm_cpp ${NJM_CPP_SRCS})
target_include_directories(njm_cpp PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(njm_cpp PUBLIC njm_cpp_boost njm_cpp_gsl njm_cpp_glog
  njm_cpp_blas)


if(${NJM_CPP_BUILD_TESTS})
  set(NJM_CPP_TEST_SRCS
    ## data
    test/data/test_trapperKeeper.cpp

    ## linalg
    test/linalg/test_stdVectorAlgebra.cpp

    ## optim
    test/optim/test_simPerturb.cpp

    ## thread
    test/thread/test_pool.cpp

    ## tools
    test/tools/test_bitManip.cpp
    test/tools/test_experiment.cpp
    test/tools/test_progress.cpp
    test/tools/test_random.cpp
    test/tools/test_stats.cpp)

  foreach(test_src ${NJM_CPP_TEST_SRCS})
    get_filename_component(test_bin ${test_src} NAME_WE)
    get_filename_component(test_dir ${test_src} DIRECTORY)
    add_executable(njm_cpp_${test_bin} ${test_src})
    set_target_properties(njm_cpp_${test_bin} PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${test_dir}")
    target_link_libraries(njm_cpp_${test_bin} njm_cpp gtest)
    add_test(njm_cpp_${test_bin}
      "${CMAKE_CURRENT_BINARY_DIR}/${test_dir}/njm_cpp_${test_bin}")
  endforeach(test_src)

endif()
