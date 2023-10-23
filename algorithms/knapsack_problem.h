
#include <vector>

namespace algorithms {

int knapsack_problem(std::vector<int> const& values, std::vector<int> const& weights, int capacity) {
  int num_items{static_cast<int>(values.size())};
  std::vector<std::vector<int>> bottom_up(num_items + 1, std::vector<int>(capacity + 1, 0));

  for (int i = 1; i <= num_items; ++i) {
    for (int j = 1; j <= capacity; ++j) {
      if (weights[i - 1] > j) {
        bottom_up[i][j] = bottom_up[i - 1][j];
      } else {
        bottom_up[i][j] = std::max(bottom_up[i - 1][j], bottom_up[i - 1][j - weights[i - 1]] + values[i - 1]);
      }
    }
  }

  return bottom_up[num_items][capacity];
}

int knapsack_big(std::vector<int> const& values, std::vector<int> const& weights, int capacity) {
  int num_items{static_cast<int>(values.size())};
  std::vector<int> previous(capacity + 1, 0);
  std::vector<int> current(capacity + 1, 0);

  for (int i = 1; i <= num_items; ++i) {
    for (int j = 1; j <= capacity; ++j) {
      if (weights[i - 1] > j) {
        current[j] = previous[j];
      } else {
        current[j] = std::max(previous[j], previous[j - weights[i - 1]] + values[i - 1]);
      }
    }
    previous = current;
  }

  return current[capacity];
}

}  // namespace algorithms
