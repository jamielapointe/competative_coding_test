
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;  // NOLINT

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'plusMinus' function below.
 *
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

static void naivePlusMinus(vector<int> arr) {
  std::size_t num_positives{0};
  std::size_t num_negatives{0};
  std::size_t num_zeroes{0};

  for (auto const &item : arr) {
    if (item > 0) {
      ++num_positives;
    } else if (item < 0) {
      ++num_negatives;
    } else {
      ++num_zeroes;
    }
  }

  // assume arr.size() > 0 based on given assumptions
  auto const inv_num_arr_size{1.0 / static_cast<double>(arr.size())};
  std::cout << static_cast<double>(num_positives) * inv_num_arr_size
            << std::endl;
  std::cout << static_cast<double>(num_negatives) * inv_num_arr_size
            << std::endl;
  std::cout << static_cast<double>(num_zeroes) * inv_num_arr_size << std::endl;
}

static void searchPlusMinus(vector<int> arr) {
  int64_t num_positives{0};
  int64_t num_negatives{0};
  int64_t num_zeroes{0};

  sort(arr.begin(), arr.end());

  auto const &arr_begin = arr.begin();
  auto const &arr_end = arr.end();
  auto const &arr_size = arr.size();

  auto first_zero_it = find(arr_begin, arr_end, 0);
  auto is_positive = [](int i) { return i > 0; };
  auto first_positive_it = find_if(arr_begin, arr_end, is_positive);

  if (arr[0] < 0) {
    num_negatives =
        first_zero_it != arr_end
            ? first_zero_it - arr_begin
            : (first_positive_it != arr_end ? first_positive_it - arr_begin
                                            : static_cast<int64_t>(arr_size));
  }
  if (first_positive_it != arr_end) {
    num_positives = arr_end - first_positive_it;
  }
  num_zeroes = static_cast<int64_t>(arr_size) - num_negatives - num_positives;

  // assume arr.size() > 0 based on given assumptions
  auto const inv_num_arr_size{1.0 / static_cast<double>(arr_size)};
  std::cout << static_cast<double>(num_positives) * inv_num_arr_size
            << std::endl;
  std::cout << static_cast<double>(num_negatives) * inv_num_arr_size
            << std::endl;
  std::cout << static_cast<double>(num_zeroes) * inv_num_arr_size << std::endl;
}

int main() {
  static constexpr std::size_t n{6};

  string arr_temp_temp{"-1, 0, 2, 4, -7, 8"};
  vector<string> arr_temp = split(ltrim(rtrim(arr_temp_temp)));

  vector<int> arr(n);

  for (std::size_t i = 0; i < n; i++) {
    int arr_item = stoi(arr_temp[i]);

    arr[i] = arr_item;
  }

  naivePlusMinus(arr);
  searchPlusMinus(arr);

  return 0;
}

string ltrim(const string &str) {
  string s(str);

  s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
          }));

  return s;
}

string rtrim(const string &str) {
  string s(str);

  s.erase(find_if(s.rbegin(), s.rend(),
                  [](unsigned char ch) { return !std::isspace(ch); })
              .base(),
          s.end());

  return s;
}

vector<string> split(const string &str) {
  vector<string> tokens;

  string::size_type start = 0;
  string::size_type end = 0;

  while ((end = str.find(" ", start)) != string::npos) {
    tokens.push_back(str.substr(start, end - start));

    start = end + 1;
  }

  tokens.push_back(str.substr(start));

  return tokens;
}
