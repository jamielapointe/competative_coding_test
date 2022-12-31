
#include <array>
#include <list>

#include "utilities.h"

namespace algorithms {

template <typename Array>
concept Bracket_Operator = requires(Array arr) { arr[0]; };

template <typename Iterator>
concept Backward_Operator = requires(Iterator it) { it--; };

/// Iterative Insertion Sort
/// Very simple sort algorithm that works on a contiguous array or vector
/// that uses an operator[](int)
/// The array is sorted in place
/// This simple example sorts thing
template <typename Array>
void insertion_sort(Array& arr)
  requires Bracket_Operator<Array>
{
  // Base case
  if (arr.size() <= 1) {
    return;
  }

  int j{0};
  for (std::size_t i{1}; i < arr.size(); ++i) {
    j = static_cast<int>(i) - 1;
    auto key = arr.at(i);

    // j is indexing to everything less than i index
    // While the array value at the j index is less than the array value at the
    // i index
    while (j >= 0 && arr.at(static_cast<std::size_t>(j)) > key) {
      arr.at(static_cast<std::size_t>(j + 1)) =
          arr.at(static_cast<std::size_t>(j));
      --j;
    }
    arr.at(static_cast<std::size_t>(j + 1)) = key;
  }
}

template <typename Iterator>
void insertion_sort(Iterator begin_it, Iterator end_it)
  requires Backward_Operator<Iterator>
{
  // Base cases
  if (begin_it == end_it) {
    return;
  }
  Iterator begin_it1{begin_it};
  ++begin_it1;
  if (begin_it == begin_it1) {
    return;
  }

  Iterator begin_it_m1{begin_it};
  --begin_it_m1;

  Iterator i = begin_it;
  Iterator j = i;
  ++i;
  while (i != end_it) {
    auto key = *i;

    while (j != begin_it_m1 && *j > key) {
      Iterator j1 = j;
      ++j1;
      *j1 = *j;
      --j;
    }
    ++j;
    *j = key;

    j = i;
    ++i;
  }
}

}  // namespace algorithms
