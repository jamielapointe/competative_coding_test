
cmake_minimum_required(VERSION 3.22.1)
project(lapointe_algorithms
    VERSION 0.0.1
    DESCRIPTION "Practics set of basic algorithms"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20 CACHE STRING "C++ standard to conform to")
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

set(LaPointe_Alg_Base_Dir ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(third_party)

option(LaPointe_Enable_Clang_Tidy "Enable Clang Tidy static analysis" ON)

if(LaPointe_Enable_Clang_Tidy)
    set(CMAKE_CXX_CLANG_TIDY clang-tidy;)
endif()

add_executable(graph_scc)

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
          -Wno-unsafe-buffer-usage
        )
    endif()
endif()

add_subdirectory(algorithms)
add_subdirectory(coursera)
add_subdirectory(hacker_rank)
add_subdirectory(leet_code)

file(COPY data/ DESTINATION data/)
