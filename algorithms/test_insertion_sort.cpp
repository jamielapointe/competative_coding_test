#include <gtest/gtest.h>

#include <random>

#include "insertion_sort.h"
#include "test_utilities.h"

namespace {

class InsertionSortTest : public ::testing::Test {
 protected:
  void SetUp() override {
    generator.seed(rd());
    std::uniform_int_distribution<int>::param_type p_type(-max_int, max_int);
    distribution.param(p_type);
  }

  inline int random_int() { return distribution(generator); }

  static constexpr int max_int{500};
  std::random_device rd{};                          // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)
  std::mt19937 generator{};                         // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)
  std::uniform_int_distribution<int> distribution;  // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)
};

TEST_F(InsertionSortTest, Array0) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  std::array<int, 1> test_array{};
  test_array[0] = random_int();
  algorithms::insertion_sort(test_array);
  EXPECT_TRUE(algorithms::is_sorted(test_array));
}

TEST_F(InsertionSortTest, Array1) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  static constexpr int32_t array_size{25};
  std::array<int, array_size> test_array{};
  for (std::size_t i = 0; i < array_size; ++i) {
    test_array.at(i) = random_int();
  }
  algorithms::insertion_sort(test_array);
  EXPECT_TRUE(algorithms::is_sorted(test_array));
}

TEST_F(InsertionSortTest, List0) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  static constexpr int32_t list_size{25};
  std::list<int> my_list{};
  for (std::size_t i = 0; i < list_size; ++i) {
    my_list.emplace_back(random_int());
  }
  algorithms::insertion_sort(my_list.begin(), my_list.end());
  EXPECT_TRUE(algorithms::is_sorted(my_list));
}

}  // namespace
