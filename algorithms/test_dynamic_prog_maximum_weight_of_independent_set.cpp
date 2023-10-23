#include <gtest/gtest.h>

#include <fstream>
#include <string>
#include <string_view>

#include "config.h"
#include "dynamic_prog_maximum_weight_of_independent_set.h"

using namespace std;
using algorithms::maximum_weight_independent_set;

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)

TEST(MaximumWeightIndependentSetTest, Test0) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  vector<int> data{20, 8, 4, 12, 10, 14, 22, 25};
  vector<int> result = maximum_weight_independent_set(data);
  vector<int> expected{1, 4, 6, 8};
  EXPECT_EQ(result, expected);
}

TEST(MaximumWeightIndependentSetTest, Test1) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  vector<int> data{1, 4, 5, 4};
  vector<int> result = maximum_weight_independent_set(data);
  vector<int> expected{2, 4};
  EXPECT_EQ(result, expected);
}

static inline vector<int> get_data(std::string_view fname) {
  ifstream data_file(fname.data());
  string line;
  getline(data_file, line);
  int number_of_symbols{0};
  istringstream ss(line);
  ss >> number_of_symbols;
  vector<int> data;
  for (; getline(data_file, line);) {
    istringstream ss1(line);
    int weight{0};
    ss1 >> weight;
    data.push_back(weight);
  }
  return data;
}

TEST(MaximumWeightIndependentSetTest, TestCoursera) {
  string const base_dir(EXECUTABLE_BASE_DIR);
  string const fname("/data/mwis.txt");
  string const full_path = base_dir + fname;
  auto data = get_data(full_path);
  EXPECT_EQ(data.size(), 1000);

  vector<int> num_to_check_in_set{1, 2, 3, 4, 17, 117, 517, 997};

  vector result = maximum_weight_independent_set(data);

  stringstream result_set;
  for (auto const& num : num_to_check_in_set) {
    int tmp_num = num;
    int tmp = std::binary_search(result.begin(), result.end(), tmp_num) ? 1 : 0;
    result_set << tmp;
  }
  EXPECT_EQ(result_set.str(), "10100110");
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
