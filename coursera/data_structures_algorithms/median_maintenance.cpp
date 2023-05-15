#include <algorithm>
#include <array>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string_view>
#include <vector>

#include "binary_heap.h"
#include "config.h"
#include "median_heaps.h"
#include "utilities.h"

using namespace std;
using namespace algorithms;

static int process_data(std::string_view fname) {
  ifstream data_file{fname.data()};
  // allow the counting of new line characters
  data_file.unsetf(std::ios_base::skipws);
  // count the new lines with a C++ STL algorithm
  auto num_nodes = std::count(std::istream_iterator<char>(data_file), std::istream_iterator<char>(), '\n');
  // init Binary Heap with capacity of data file
  Median_Heaps<int> median_heaps(static_cast<int>(num_nodes));
  data_file.clear();   // clear the EOF flag
  data_file.seekg(0);  // go to start of file

  // parse each line
  // adding each line to binary heap and computing the m_k median and
  // adding it to the cumulative sum of medians
  int median_sum{0};
  int debug_counter{0};
  for (std::string line; std::getline(data_file, line);) {
    std::istringstream ss(line);
    int x_k{0};
    ss >> x_k;
    median_heaps.insert(x_k);
    int m_k = median_heaps.compute_median();
    median_sum += m_k;
    ++debug_counter;
  }
  static constexpr int expected_count{10'000};
  if (debug_counter != expected_count) {
    cout << "ERROR: actual count = " << debug_counter << ", expected = " << expected_count << "\n";
  }
  return median_sum;
}

static void run_coursera() {
  cout << "Coursera Quiz Median Maintenance\n";

  std::string const base_dir(EXECUTABLE_BASE_DIR);
  std::string const fname("/data/medianData.txt");
  std::string const full_path = base_dir + fname;
  auto median_sum = process_data(full_path);
  static constexpr int modulo_value{10'000};
  auto answer = median_sum % modulo_value;

  cout << "\n";
  cout << "The cumulative sum of the medians modulo 10,000 is: " << answer << "\n\n";
}

int main() {
  run_coursera();

  return 0;
}
