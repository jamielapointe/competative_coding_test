
add_executable(branchless_benchmark
  01a_branch_predicted.cpp
  01b_branch_mispredicted.j.cpp
  01c_branch_predicted.j.cpp
  01d_bad_hint.cpp
  # 02a_false_branch.cpp
  # 02b_false_branch.cpp
  # 02c_false_branch.cpp
  # 03a_branch.cpp
  # 03b_branchless.cpp
  # 03c_branch_predicted.cpp
  # 03d_branchless_predicted.cpp
  # 04a_branch.cpp
  # 04b_branchless.cpp
  # 04c_branch.cpp
  # 04d_branchless.cpp
  # 05a_branch.cpp
  # 05b_branchless.cpp
  # 06a_func_branch.cpp
  # 06b_func_branchless.cpp
  # 07a_binpow_branch.cpp
  # 07b_binpow_branchless.cpp
  # 07c_binpow2_branch.cpp
  # 07d_binpow2_branchless.cpp
  branchless_benchmark_main.cpp
)

if (LaPointe_Enable_Sample_Based_Profiling)
  target_compile_options(branchless_benchmark PRIVATE -fprofile-instr-generate)
endif()

target_compile_options(branchless_benchmark PRIVATE -march=native)

if (LaPointe_Enable_LTO)
  target_compile_options(branchless_benchmark PRIVATE -flto)
  if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    find_program(GCC_AR gcc-ar)
    if (GCC_AR)
      set(CMAKE_AR ${GCC_AR})
    endif()
    find_program(GCC_RANLIB gcc-ranlib)
    if (GCC_RANLIB)
      set(CMAKE_RANLIB ${GCC_RANLIB})
    endif()
  elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    include(llvm-toolchain)
  endif()
endif()

if (HAVE_LIBPFM)
  target_link_libraries(branchless_benchmark PRIVATE pfm)
  target_compile_definitions(branchless_benchmark PRIVATE -DHAVE_LIBPFM)
endif()

target_compile_options(branchless_benchmark PRIVATE -fno-exceptions)
target_compile_options(branchless_benchmark PRIVATE -Wno-weak-vtables)
target_compile_options(branchless_benchmark PRIVATE -Wno-global-constructors)
target_compile_options(branchless_benchmark PRIVATE -Wno-unused-member-function)

target_include_directories(branchless_benchmark PRIVATE ${BENCHMARK_INCLUDE})

target_link_libraries(branchless_benchmark PRIVATE benchmark::benchmark)

# if (LaPointe_Enable_Sample_Based_Profiling)
#   target_link_libraries(branchless_benchmark PRIVATE profiler)
# endif()

target_link_libraries(branchless_benchmark PRIVATE Threads::Threads)
