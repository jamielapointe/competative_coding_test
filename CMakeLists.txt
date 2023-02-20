
cmake_minimum_required(VERSION 3.25)
project(lapointe_algorithms
    VERSION 0.0.1
    DESCRIPTION "Practice set of basic algorithms"
    LANGUAGES CXX)

add_subdirectory(third_party SYSTEM)

set(CMAKE_CXX_STANDARD 20 CACHE STRING "C++ standard to conform to")
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

set(LaPointe_Alg_Base_Dir ${CMAKE_CURRENT_SOURCE_DIR})

set(BENCHMARK_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/googlebenchmark/include)
message(STATUS ${BENCHMARK_INCLUDE})

option(LaPointe_Enable_Clang_Tidy "Enable Clang Tidy static analysis" ON)
option(LaPointe_Enable_LTO "Enable Link Time Optimization (LTO)" OFF)
option(LaPointe_Enable_PFM "Enable libpfm" OFF)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  option(LaPointe_Enable_Sample_Based_Profiling "Enable Clang sample based profiling" ON)
endif()

if(LaPointe_Enable_Clang_Tidy)
    set(CMAKE_CXX_CLANG_TIDY clang-tidy;)
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR})

if((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
    add_compile_options(
        -Werror
        -Wno-padded
      )

    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        add_compile_options(
          -Wall
        )
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        add_compile_options(
          -Weverything
          -Wno-pre-c++17-compat
          -Wno-c++98-compat
          -Wno-c++98-compat-pedantic
        )
        if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 16)
          add_compile_options(
            -Wno-unsafe-buffer-usage
          )
        endif()
    endif()
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/third_party/googlebenchmark/cmake/Modules")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/third_party/googlebenchmark/cmake")

include(AddCXXCompilerFlag)
include(CheckCXXCompilerFlag)
include(CheckLibraryExists)
include(CXXFeatureCheck)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

if (LaPointe_Enable_PFM)
  find_package(PFM REQUIRED)
endif()

add_subdirectory(algorithms)
add_subdirectory(branchless_benchmark)
add_subdirectory(coursera)
add_subdirectory(hacker_rank)
add_subdirectory(leet_code)

file(COPY data/ DESTINATION data/)
