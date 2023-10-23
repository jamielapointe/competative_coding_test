#include <gtest/gtest.h>

#include <array>

#include "optimal_binary_search_tree.h"

using std::array;

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)

TEST(OptimalBinarySearchTreeTest, Test0) {
  array<int, 3> keys{10, 12, 20};
  array<int, 3> frequencies{34, 8, 50};
  auto result = algorithms::optimal_binary_search_tree(keys, frequencies);
  EXPECT_EQ(result.cost, 142);
}

TEST(OptimalBinarySearchTreeTest, Test1) {
  array<int, 4> keys{10, 12, 16, 21};
  array<int, 4> frequencies{4, 2, 6, 3};
  auto result = algorithms::optimal_binary_search_tree(keys, frequencies);
  EXPECT_EQ(result.cost, 26);
}

TEST(OptimalBinarySearchTreeTest, Test2) {
  array<int, 5> keys{10, 20, 30, 40, 50};
  array<int, 5> frequencies{5, 4, 3, 2, 1};
  auto result = algorithms::optimal_binary_search_tree(keys, frequencies);
  EXPECT_EQ(result.cost, 30);
}

TEST(OptimalBinarySearchTreeTest, Test3) {
  array<int, 7> keys{1, 2, 3, 4, 5, 6, 7};
  array<int, 7> frequencies{20, 5, 17, 10, 20, 3, 25};
  auto result = algorithms::optimal_binary_search_tree(keys, frequencies);
  EXPECT_EQ(result.cost, 223);
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
