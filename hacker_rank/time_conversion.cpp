#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'timeConversion' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

static inline vector<string> split(string const &str,
                                   string const &split_char) {
  vector<string> tokens;

  string::size_type start = 0;
  string::size_type end = 0;

  while ((end = str.find(split_char, start)) != string::npos) {
    tokens.push_back(str.substr(start, end - start));

    start = end + 1;
  }

  tokens.push_back(str.substr(start));

  return tokens;
}

// trim from start (in place)
static inline std::string &ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
          }));
  return s;
}

// trim from end (in place)
static inline std::string &rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       [](unsigned char ch) { return !std::isspace(ch); })
              .base(),
          s.end());
  return s;
}

static inline string timeConversion(string s) {
  static constexpr std::size_t k_timeStringLength{8};
  static constexpr uint32_t k_maxHour{12};
  rtrim(ltrim(s));
  std::string time = s.substr(0, k_timeStringLength);
  std::string am_pm = s.substr(k_timeStringLength);
  std::vector<string> split_time = split(time, ":");
  auto hour{stoi(split_time[0])};
  if (hour == k_maxHour && am_pm == "AM") {
    hour = 0;
  } else if (hour != k_maxHour && am_pm == "PM") {
    hour += k_maxHour;
  }
  stringstream ss;
  ss << setw(2) << setfill('0') << hour;
  string hour_string = ss.str();

  stringstream ss2;
  ss2 << hour_string << ":" << split_time[1] << ":" << split_time[2];
  return ss2.str();
}

int main() {
  ofstream fout(getenv("OUTPUT_PATH"));

  string s;
  getline(cin, s);

  string result = timeConversion(s);

  fout << result << "\n";

  fout.close();

  return 0;
}
