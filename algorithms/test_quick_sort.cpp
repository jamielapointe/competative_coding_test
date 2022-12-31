#include <random>

#include "gtest/gtest.h"
#include "quick_sort.h"

namespace {

class QuickSortTest : public ::testing::Test {
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

TEST_F(QuickSortTest, Array0) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  std::array<int, 1> test_array{};
  test_array[0] = random_int();
  static constexpr int32_t min_index{0};
  int32_t const max_index{static_cast<int32_t>(test_array.size()) - 1};
  algorithms::quick_sort(test_array, min_index, max_index);
  EXPECT_TRUE(algorithms::is_sorted(test_array));
}

TEST_F(QuickSortTest, Array1) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  static constexpr int32_t array_size{25};
  std::array<int, array_size> test_array{};
  for (std::size_t i = 0; i < array_size; ++i) {
    test_array.at(i) = random_int();
  }
  static constexpr int32_t min_index{0};
  int32_t const max_index{static_cast<int32_t>(test_array.size()) - 1};
  algorithms::quick_sort(test_array, min_index, max_index);
  EXPECT_TRUE(algorithms::is_sorted(test_array));
}

TEST_F(QuickSortTest, List0) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  static constexpr int32_t list_size{25};
  std::list<int> my_list{};
  for (std::size_t i = 0; i < list_size; ++i) {
    my_list.emplace_back(random_int());
  }
  algorithms::quick_sort(my_list.begin(), my_list.end());
  EXPECT_TRUE(algorithms::is_sorted(my_list));
}

}  // namespace
