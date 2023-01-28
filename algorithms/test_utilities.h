
#pragma once

#include <bits/iterator_concepts.h>

#include "gtest/gtest.h"
#include "utilities.h"

namespace algorithms {

template <typename Sorted_Container>
testing::AssertionResult is_sorted(Sorted_Container const& container)
  requires Has_Iterators<Sorted_Container>
{
  Sorted_Container copy{container};
  sort(copy);
  if (std::equal(container.begin(), container.end(), copy.begin())) {
    return testing::AssertionSuccess();
  } else {
    return testing::AssertionFailure() << get_arrays_string(container, copy);
  }
}

template <typename Container>
testing::AssertionResult are_containers_equal(Container const& container1, Container const& container2) {
  if (std::equal(container1.begin(), container1.end(), container2.begin())) {
    return testing::AssertionSuccess();
  } else {
    return testing::AssertionFailure() << get_arrays_string(container1, container2);
  }
}

}  // namespace algorithms
