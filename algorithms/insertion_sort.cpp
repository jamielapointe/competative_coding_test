
#include <array>
#include <iostream>
#include <list>
#include <random>

namespace algorithms {

template <typename Array>
concept Bracket_Operator = requires(Array arr) { arr[0]; };

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
void insertion_sort(Iterator begin_it, Iterator end_it) {
  // If there is 1 or less items in the list, then exit
  if (begin_it == end_it) {
    return;
  }
  Iterator end1_it;
  --end1_it;
  if (begin_it == end1_it) {
    return;
  }

  Iterator i = begin_it;
  Iterator j = i;
  ++i;
  while (i != end_it) {
    auto key = *i;

    while (j != begin_it && *j > key) {
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

template <typename Iterator>
void print_array(Iterator front_it, Iterator end_it) {
  while (front_it != end_it) {
    std::cout << *front_it << std::endl;
    ++front_it;
  }
  std::cout << std::endl;
}

}  // namespace algorithms

int main() {
  static constexpr int max_int{500};
  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(-max_int, max_int);

  std::cout << "Insertion Sort Test" << std::endl;

  std::cout << "Array 0 test" << std::endl;
  std::array<int, 1> arr0{};
  arr0[0] = distribution(generator);
  algorithms::insertion_sort(arr0);
  algorithms::print_array(arr0.begin(), arr0.end());

  std::cout << "Array 1 test" << std::endl;
  static constexpr int32_t arr_size{25};
  std::array<int, arr_size> arr1{};
  for (std::size_t i = 0; i < arr_size; ++i) {
    arr1.at(i) = distribution(generator);
  }
  algorithms::insertion_sort(arr1);
  algorithms::print_array(arr1.begin(), arr1.end());

  std::cout << "List 0 test" << std::endl;
  std::list<int> my_list{};
  for (std::size_t i = 0; i < arr_size; ++i) {
    my_list.emplace_back(distribution(generator));
  }
  algorithms::insertion_sort(my_list.begin(), my_list.end());
  algorithms::print_array(my_list.begin(), my_list.end());
}
