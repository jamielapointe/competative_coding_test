
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

using namespace std;

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, cppcoreguidelines-avoid-c-arrays, clang-diagnostic-sign-compare)
// NOLINTBEGIN(cppcoreguidelines-pro-bounds-array-to-pointer-decay, clang-diagnostic-unused-comparison)

class Solution {
 public:
  string reverseOnlyLetters(string s) {
    int left = 0;
    int right = static_cast<int>(s.length()) - 1;
    char ans[s.length()];
    while (left < static_cast<int>(s.length())) {
      if (!isalpha(s[left])) {
        ans[left] = s[left];
        ++left;
        continue;
      }
      if (!isalpha(s[right])) {
        --right;
        continue;
      }
      if (!isalpha(s[left])) {
        ans[left] = s[left];
        continue;
      }
      ans[left] = s[right];
      --right;
      ++left;
    }
    return string(ans, left);
  }
};

TEST(Data_Structures_And_Algorithms, ReverseOnlyLetters) {
  Solution sol;

  string test00{"ab-cd"};
  string expected00{"dc-ba"};
  EXPECT_PRED2([](auto test_str, auto expect_str) { return test_str == expect_str; }, sol.reverseOnlyLetters(test00), expected00);

  string test01{"a-bC-dEf-ghIj"};
  string expected01{"j-Ih-gfE-dCba"};
  EXPECT_PRED2([](auto test_str, auto expect_str) { return test_str == expect_str; }, sol.reverseOnlyLetters(test01), expected01);

  string test02{"Test1ng-Leet=code-Q!"};
  string expected02{"Qedo1ct-eeLg=ntse-T!"};
  EXPECT_PRED2([](auto test_str, auto expect_str) { return test_str == expect_str; }, sol.reverseOnlyLetters(test02), expected02);
}

// NOLINTEND(cppcoreguidelines-pro-bounds-array-to-pointer-decay, clang-diagnostic-unused-comparison)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, cppcoreguidelines-avoid-c-arrays, clang-diagnostic-sign-compare)
