#include <array>
#include <list>
#include <random>

#include "utilities.h"

namespace algorithms {

// This contains implementations of quick sort for contiguous random access
// iterators (such as array an vector) along with an implementation that works
// on forward iterators (such as linked list).  These show just the basic
// implementations not the optimized ones for very large containers.

template <typename Iterator>
void swap(Iterator begin_it, Iterator end_it) {
  auto tmp = *begin_it;
  *begin_it = *end_it;
  *end_it = tmp;
}
template <typename Array>
void swap(Array& arr, int a, int b) {
  auto tmp = arr.at(static_cast<std::size_t>(a));
  arr.at(static_cast<std::size_t>(a)) = arr.at(static_cast<std::size_t>(b));
  arr.at(static_cast<std::size_t>(b)) = tmp;
}

inline int pivot(int begin, int end) {
  (void)begin;
  return end;
}

template <typename Iterator>
Iterator partition(Iterator begin_it, Iterator end_it) {
  if (begin_it == end_it) {
    return begin_it;
  }

  Iterator pivot_prev_it = begin_it;
  // temporary pivot iterator
  Iterator curr_it = begin_it;
  Iterator pivot_it = end_it;

  while (begin_it != end_it) {
    // if the current element is less than the pivot element
    if (*begin_it < *pivot_it) {
      // save of the one before the pivot element
      pivot_prev_it = curr_it;
      // swap the current element with the element of the temporary pivot
      // iterator
      ::algorithms::swap(curr_it, begin_it);
      // increment the current pivot iterator
      ++curr_it;
    }
    ++begin_it;
  }

  ::algorithms::swap(curr_it, pivot_it);

  return pivot_prev_it;
}

// implement the simpler Lomuto partition scheme
template <typename Array>
int partition(Array& arr, int begin, int end, int pivot_it) {
  (void)end;
  // temporary pivot index
  int i = begin - 1;

  for (int j = begin; j <= pivot_it - 1; ++j) {
    // if the current element is less than the pivot element
    if (arr.at(static_cast<std::size_t>(j)) <= arr.at(static_cast<std::size_t>(pivot_it))) {
      // increment the temporary pivot index
      ++i;
      // swap the current element with the element at the temporary pivot index
      swap(arr, i, j);
    }
  }
  ++i;
  // move the pivot element to the correct pivot position (between the smaller
  // and larger elements)
  swap(arr, i, pivot_it);
  return i;  // the new pivot index
}

template <typename Iterator>
void quick_sort(Iterator begin_it, Iterator end_it) {
  // base case
  if (begin_it == end_it) {
    return;
  }

  auto partition_prev_it = partition(begin_it, end_it);
  quick_sort(begin_it, partition_prev_it);

  // get to the partition_next_it - checking it does not run off the end of the
  // list
  auto partition_it = partition_prev_it++;
  if (partition_it == end_it) {
    return;
  }
  auto partition_next_it = partition_prev_it++;

  quick_sort(partition_next_it, end_it);
}

template <typename Array>
void quick_sort(Array& arr, int32_t begin, int32_t end) {
  if (begin < end) {
    auto pivot_it = pivot(begin, end);
    auto partition_it = partition(arr, begin, end, pivot_it);
    quick_sort(arr, begin, partition_it - 1);
    quick_sort(arr, partition_it + 1, end);
  }
}

}  // namespace algorithms
