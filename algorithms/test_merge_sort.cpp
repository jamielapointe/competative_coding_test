#include <random>

#include "gtest/gtest.h"
#include "merge_sort.h"
#include "utilities.h"

namespace {

class MergeSortTest : public ::testing::Test {
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

TEST_F(MergeSortTest, Array0) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  std::array<int, 1> test_array{};
  test_array[0] = random_int();
  algorithms::merge_sort(test_array.begin(), test_array.end());
  EXPECT_TRUE(algorithms::is_sorted(test_array));
}

}  // namespace
