
cmake_minimum_required(VERSION 3.22.1)
project(lapointe_algorithms
    VERSION 0.0.1
    DESCRIPTION "Practics set of basic algorithms"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20 CACHE STRING "C++ standard to conform to")
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

option(LaPointe_Enable_Test "Enable Unit Tests" ON)

if(LaPointe_Enable_Clang-Tidy)
    set(CMAKE_CXX_CLANG_TIDY clang-tidy;)
endif()

add_executable(graph_scc)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graph
    ${CMAKE_BINARY_DIR})

if(MSVC)
else()
    add_compile_options(-Weverything
        -Werror
        -Wno-pre-c++17-compat
        -Wno-c++98-compat
        -Wno-c++98-compat-pedantic
        -Wno-global-constructors
        -Wno-padded)
endif()

add_subdirectory(algorithms)
add_subdirectory(coursera)
add_subdirectory(hacker_rank)
add_subdirectory(leet_code)
