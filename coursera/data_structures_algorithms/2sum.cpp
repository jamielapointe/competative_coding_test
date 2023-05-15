#include "2sum.h"

#include <algorithm>
#include <array>
#include <fstream>
#include <iterator>
#include <memory>
#include <sstream>
#include <string_view>
#include <vector>

#include "2sum.h"
#include "config.h"
#include "utilities.h"

using namespace std;
using namespace algorithms;

class Two_Sum {
 public:
  void process_data(std::string_view fname);
  int64_t run_2sum();
  int64_t run_2sum2();

  static constexpr int64_t kMinTarget{-10'000};
  static constexpr int64_t kMaxTarget{10'000};

 private:
  std::vector<int64_t> integer_list_;
};

void Two_Sum::process_data(std::string_view fname) {
  ifstream data_file{fname.data()};
  // allow the counting of new line characters
  data_file.unsetf(std::ios_base::skipws);
  // count the new lines with a C++ STL algorithm
  auto num_nodes = std::count(std::istream_iterator<char>(data_file), std::istream_iterator<char>(), '\n');
  // init Binary Heap with capacity of data file
  integer_list_.reserve(static_cast<std::size_t>(num_nodes));
  data_file.clear();   // clear the EOF flag
  data_file.seekg(0);  // go to start of file

  // parse each line
  // adding each line to binary heap and computing the m_k median and
  // adding it to the cumulative sum of medians
  for (std::string line; std::getline(data_file, line);) {
    std::istringstream ss(line);
    int64_t x_k{0};
    ss >> x_k;
    integer_list_.emplace_back(x_k);
  }
}

int64_t Two_Sum::run_2sum() {
  auto count_2sum = find_2sum<int64_t>(integer_list_, kMinTarget, kMaxTarget);
  return count_2sum;
}

static void run_coursera() {
  cout << "Coursera Quiz two sum\n";

  std::string const base_dir(EXECUTABLE_BASE_DIR);
  std::string const fname("/data/2sum.txt");
  std::string const full_path = base_dir + fname;
  auto two_sum = std::make_unique<Two_Sum>();
  two_sum->process_data(full_path);

  auto answer = two_sum->run_2sum();
  cout << "\n"
       << "The number of target values t in the interval [-10'000, 10'000] (inclusive) such that "
       << "there are distinct numbers x, y in the input file that satisfy x + y = t: " << answer << "\n\n";
}

int main() {
  run_coursera();

  return 0;
}
