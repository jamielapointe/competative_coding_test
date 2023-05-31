
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

using namespace std;
using ::testing::ElementsAreArray;

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)

class Squares_Of_Sorted_Array {
 public:
  vector<int> sortedSquares(vector<int>& nums) {
    vector<int> ans;
    if (nums.size() == 0) {
      return ans;
    }
    ans.reserve(nums.size());
    if (nums.size() == 1) {
      ans.emplace_back(nums.front() * nums.front());
      return ans;
    }
    auto j = lower_bound(nums.begin(), nums.end(), 0);
    if (j == nums.end()) {
      j = nums.end() - 1;
    }
    auto i = j - 1;
    if (j == nums.begin()) {
      i = j;
      ++j;
    }
    if (j == nums.end()) {
      j = nums.end() - 1;
    }
    while (i >= nums.begin() && j < nums.end() && i <= j) {
      if (std::abs(*i) < std::abs(*j)) {
        ans.emplace_back((*i) * (*i));
        --i;
        continue;
      }
      ans.emplace_back((*j) * (*j));
      ++j;
    }
    while (i >= nums.begin() && i <= j) {
      ans.emplace_back((*i) * (*i));
      --i;
    }
    while (j < nums.end() && i <= j) {
      ans.emplace_back((*j) * (*j));
      ++j;
    }
    return ans;
  }
};

TEST(Data_Structures_And_Algorithms, SquaresOfSortedArray) {
  Squares_Of_Sorted_Array solution;

  vector<int> nums{-4, -1, 0, 3, 10};
  vector<int> expected{0, 1, 9, 16, 100};
  auto answer = solution.sortedSquares(nums);
  ASSERT_THAT(answer, ElementsAreArray(expected));

  vector<int> nums1{1, 2, 3, 10};
  vector<int> expected1{1, 4, 9, 100};
  auto answer1 = solution.sortedSquares(nums1);
  ASSERT_THAT(answer1, ElementsAreArray(expected1));

  vector<int> nums2{-10, -3, -2, -1};
  vector<int> expected2{1, 4, 9, 100};
  auto answer2 = solution.sortedSquares(nums2);
  ASSERT_THAT(answer2, ElementsAreArray(expected2));

  vector<int> nums3{-10, -3, -2, -1, 0};
  vector<int> expected3{0, 1, 4, 9, 100};
  auto answer3 = solution.sortedSquares(nums3);
  ASSERT_THAT(answer3, ElementsAreArray(expected3));

  vector<int> nums4{1};
  vector<int> expected4{1};
  auto answer4 = solution.sortedSquares(nums4);
  ASSERT_THAT(answer4, ElementsAreArray(expected4));

  vector<int> nums5{-1};
  vector<int> expected5{1};
  auto answer5 = solution.sortedSquares(nums5);
  ASSERT_THAT(answer5, ElementsAreArray(expected5));
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
