
#pragma once

#include <bits/iterator_concepts.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>

namespace algorithms {

template <typename Iterator>
void print_array(Iterator front_it, Iterator end_it) {
  while (front_it != end_it) {
    std::cout << *front_it << std::endl;
    ++front_it;
  }
  std::cout << std::endl;
}

template <typename Container>
std::string get_arrays_string(Container const& actual, Container const& expected) {
  std::stringstream ss;
  if (actual.size() != expected.size()) {
    ss << "Sizes of containers do not match; actual = " << actual.size() << " -- expected = " << expected.size() << std::endl;
    return ss.str();
  }
  auto actual_it = actual.begin();
  auto expected_it = expected.begin();
  while (actual_it != actual.end()) {
    ss << *actual_it << " - " << *expected_it << "\n";
    ++actual_it;
    ++expected_it;
  }
  return ss.str();
}

template <typename Container>
concept Has_Iterators = requires(Container it) {
  it.begin();
  it.end();
};

template <typename Container>
void test_containers_equal(Container const& actual, Container const& expected)
  requires Has_Iterators<Container>
{
  assert(std::equal(actual.begin(), actual.end(), expected.begin()));
  std::cout << "Test Passed" << std::endl;
}

template <typename Container>
concept Sort_Operator = requires(Container it) { it.sort(); };

template <typename Container>
void sort(Container& container)
  requires Sort_Operator<Container>
{
  container.sort();
}

template <typename Container>
void sort(Container& container)
  requires std::random_access_iterator<typename Container::iterator>
{
  std::sort(container.begin(), container.end());
}

template <typename Sorted_Container>
void test_sort(Sorted_Container const& container) {
  Sorted_Container copy{container};
  sort(copy);
  test_containers_equal(container, copy);
}

}  // namespace algorithms
