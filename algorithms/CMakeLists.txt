add_executable(
  test_algorithms
  test_binary_heap.cpp
  test_breadth_first_search_ordered.cpp
  test_breadth_first_search_unordered.cpp
  test_depth_first_search_unordered.cpp
  test_dijkstras_shortest_path.cpp
  test_dynamic_prog_maximum_weight_of_independent_set.cpp
  test_huffman_frequency.cpp
  test_insertion_sort.cpp
  test_knapsack_problem.cpp
  test_main.cpp
  test_max_spacing_k_clustering.cpp
  test_optimal_binary_search_tree.cpp
  test_quick_sort.cpp
  test_strongly_connected_components_ordered.cpp)

target_include_directories(test_algorithms PRIVATE GoogleTest)
target_link_libraries(test_algorithms PRIVATE GTest::gtest_main)
target_compile_options(
  test_algorithms PRIVATE -Wno-weak-vtables -Wno-global-constructors
                          -Wno-unused-member-function)
