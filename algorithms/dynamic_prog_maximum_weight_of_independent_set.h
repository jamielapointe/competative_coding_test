
#include <algorithm>
#include <vector>

namespace algorithms {

std::vector<int> maximum_weight_independent_set(std::vector<int> const& weights) {
  int num_weights{static_cast<int>(weights.size())};
  std::vector<int> bottom_up(num_weights + 1, 0);

  // Computer MWIS using a bottom up approach.
  bottom_up[1] = weights[0];
  for (int i = 2; i <= num_weights; ++i) {
    bottom_up[i] = std::max(bottom_up[i - 1], bottom_up[i - 2] + weights[i - 1]);
  }

  // Reconstruction of the MWIS.
  std::vector<int> result;
  int i = num_weights;
  while (i > 0) {
    if (bottom_up[i - 1] == bottom_up[i]) {  // case 1: i is not in the MWIS. (current [last] node is excluded)
      --i;
    } else {                // case 2: current node is included in the MWIS.
      result.push_back(i);  // 1 based index
      i -= 2;
    }
  }

  // Reverse the result.
  std::reverse(result.begin(), result.end());

  return result;
}

}  // namespace algorithms
