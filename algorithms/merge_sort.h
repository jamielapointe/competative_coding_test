
#include <algorithm>
#include <ranges>
#include <vector>

namespace algorithms {

template <typename Iterator>
void merge_sort(Iterator begin_it, Iterator end_it) {
  // check base cases
  if (begin_it == end_it) return;
  auto next_it = begin_it;
  ++next_it;
  if (next_it == end_it) return;

  // spit container into left and right halves
  auto num_items = std::distance(begin_it, end_it);
  auto middle_count = num_items / 2 + 1;
  auto middle_it = std::advance(begin_it, middle_count);
  std::vector<typename Iterator::value_type> left(std::distance(begin_it, middle_it));
  std::vector<typename Iterator::value_type> right(std::distance(middle_it, end_it));
  std::ranges::copy(begin_it, middle_it, std::back_inserter(left));
  std::ranges::copy(middle_it, end_it, std::back_inserter(right));

  // Use divide and conquer algorithm to sort the split containers
  merge_sort(left.begin(), left.end());
  merge_sort(right.begin(), right.end());

  // Merge the left and right sides back into the original container
  std::merge(left.begin(), left.end(), right.begin(), right.end(), begin_it);
}

}  // namespace algorithms
