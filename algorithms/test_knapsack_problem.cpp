#include <gtest/gtest.h>

#include <fstream>
#include <string>
#include <string_view>

#include "config.h"
#include "knapsack_problem.h"

using algorithms::knapsack_big;
using algorithms::knapsack_problem;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)

TEST(KnapsackTest, Test0) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  vector<int> values{60, 100, 120};
  vector<int> weights{10, 20, 30};
  int capacity = 50;
  EXPECT_EQ(knapsack_problem(values, weights, capacity), 220);
  EXPECT_EQ(knapsack_big(values, weights, capacity), 220);
}

TEST(KnapsackTest, Test1) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  vector<int> values{1, 4, 5, 4};
  vector<int> weights{1, 2, 3, 4};
  int capacity = 4;
  EXPECT_EQ(knapsack_problem(values, weights, capacity), 6);
  EXPECT_EQ(knapsack_big(values, weights, capacity), 6);
}

struct KnapsackData {
  vector<int> values;
  vector<int> weights;
  int capacity;
  int expected;
};

static inline KnapsackData get_data(std::string_view fname) {
  ifstream data_file(fname.data());
  string line;
  getline(data_file, line);
  int capacity{0};
  istringstream ss(line);
  ss >> capacity;
  int number_of_items{0};
  ss >> number_of_items;
  KnapsackData data;
  data.capacity = capacity;
  data.values.reserve(number_of_items);
  data.weights.reserve(number_of_items);
  for (; getline(data_file, line);) {
    istringstream ss1(line);
    int value{0};
    int weight{0};
    ss1 >> value;
    ss1 >> weight;
    data.values.push_back(value);
    data.weights.push_back(weight);
  }
  return data;
}

TEST(KnapsackTest, TestCoursera0) {
  string const base_dir(EXECUTABLE_BASE_DIR);
  string const fname("/data/knapsack1.txt");
  string const full_path = base_dir + fname;
  auto data = get_data(full_path);
  data.expected = 2493893;
  EXPECT_EQ(data.values.size(), 100);
  EXPECT_EQ(data.weights.size(), 100);

  int result = knapsack_problem(data.values, data.weights, data.capacity);
  EXPECT_EQ(result, data.expected);
}

TEST(knapsackTest, TestCoursera1) {
  string const base_dir(EXECUTABLE_BASE_DIR);
  string const fname("/data/knapsack_big.txt");
  string const full_path = base_dir + fname;
  auto data = get_data(full_path);
  data.expected = 4243395;
  EXPECT_EQ(data.values.size(), 2000);
  EXPECT_EQ(data.weights.size(), 2000);

  int result = knapsack_big(data.values, data.weights, data.capacity);
  EXPECT_EQ(result, data.expected);
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
