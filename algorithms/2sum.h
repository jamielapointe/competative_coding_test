#pragma once

#include <algorithm>
#include <span>
#include <unordered_set>
#include <utility>
#include <vector>

namespace algorithms {

///@brief count the number of unique numbers to sum to t in the range [-10000, 10000]
/// Compute the number of target values \f$t\f$ in the interval
/// \f$[-10'000, 10'000]\f$ (inclusive) such that there are distinct numbers,
/// \f$x,y\f$ in the input file that satisfy \f$x + y = t\f$
///@tparam Integer the type of integer (e.g., int32_t, int64_t)
///@param input a read-only view of a container of integers
///@param min_target the lower bound of the integer range
///@param max_target the upper bound (inclusive) of the integer range
///@return The number of unique sum targets found in the list
template <typename Integer>
Integer find_2sum(std::vector<Integer> input, Integer min_target, Integer max_target) {
  std::sort(input.begin(), input.end());
  Integer number_unique_targets{0};
  std::unordered_set<Integer> seen_targets;
  seen_targets.reserve(input.size());
  for (auto value : input) {
    auto min_value = min_target - value;
    auto max_value = max_target - value;
    auto l_bound = std::lower_bound(input.begin(), input.end(), min_value);
    auto u_bound = std::upper_bound(input.begin(), input.end(), max_value);
    auto lb_dist = std::distance(input.begin(), l_bound);
    (void)lb_dist;
    auto ub_dist = std::distance(input.begin(), u_bound);
    (void)ub_dist;

    for (auto compliment_it = l_bound; compliment_it != u_bound; ++compliment_it) {
      auto dist = std::distance(input.begin(), compliment_it);
      (void)dist;
      auto compliment = *compliment_it;
      auto sum = value + compliment;
      if (!seen_targets.contains(sum)) {
        seen_targets.emplace(sum);
        ++number_unique_targets;
      }
    }
  }
  return number_unique_targets;
}

}  // namespace algorithms
