#include <iostream>
#include <limits>
#include <memory>
#include <vector>

using std::vector;

class Solution {
 public:
  int nearestValidPoint(int x, int y, vector<vector<int>>& points) {
    int min_distance{std::numeric_limits<int>::max()};
    int min_distance_index{-1};
    for (uint32_t index{0}; index < points.size(); ++index) {
      auto const& point{points[index]};  // NOLINT this is safe
      if (point[0] != x && point[1] != y) {
        continue;
      }
      int tmp_distance = manhattan_distance(x, y, point[0], point[1]);
      if (tmp_distance < min_distance) {
        min_distance_index = static_cast<int>(index);
        min_distance       = tmp_distance;
      }
    }
    return min_distance_index;
  }

  int manhattan_distance(int x1, int y1, int x2, int y2) { return abs(x1 - x2) + abs(y1 - y2); }
};

int main() {
  std::unique_ptr<Solution> solution = std::make_unique<Solution>();
  int                       x{3};
  int                       y{4};
  vector<vector<int>>       points{
      {1, 2},
      {3, 1},
      {2, 4},
      {2, 3},
      {4, 4}
  };
  auto my_answer = solution->nearestValidPoint(x, y, points);
  int  expected_answer{2};
  if (my_answer != expected_answer) {
    std::cout << "WRONG; "
              << "expected answer = " << expected_answer << ", my answer: " << my_answer << std::endl;
  } else {
    std::cout << "Correct!" << std::endl;
  }
  return 0;
}
