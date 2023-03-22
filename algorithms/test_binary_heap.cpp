#include <gtest/gtest.h>

#include "binary_heap.h"
#include "median_heaps.h"
#include "test_utilities.h"
#include "utilities.h"

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)

namespace {

static int get_median(std::vector<int> const& data_set) {
  if (algorithms::is_even(data_set.size())) {
    return data_set.at(data_set.size() / 2 - 1);
  }
  return data_set.at((data_set.size() + 1) / 2 - 1);
}

TEST(BinaryHeapTest, Basic00) {
  static constexpr int heap_capacity{6};
  algorithms::Binary_Heap<int> binary_heap(heap_capacity);
  ASSERT_EQ(binary_heap.capacity(), heap_capacity);
  ASSERT_EQ(binary_heap.size(), 0);
  binary_heap.insert(0);
  ASSERT_EQ(binary_heap.size(), 1);
  ASSERT_EQ(binary_heap.get_min(), 0);
  binary_heap.insert(5);
  ASSERT_EQ(binary_heap.get_min(), 0);
  binary_heap.insert(-5);
  ASSERT_EQ(binary_heap.get_min(), -5);
  binary_heap.insert(-3);
  ASSERT_EQ(binary_heap.get_min(), -5);
  binary_heap.insert(2);
  ASSERT_EQ(binary_heap.get_min(), -5);
  binary_heap.insert(-7);
  ASSERT_EQ(binary_heap.get_min(), -7);
  ASSERT_EQ(binary_heap.size(), heap_capacity);
  ASSERT_EQ(binary_heap.capacity(), heap_capacity);
}

TEST(BinaryHeapTest, Basic01) {
  std::array data_set{
      6331, 2793, 1640, 9290, 225, 625,  6195, 2303, 5685, 1354, 4292, 7600, 6447, 4479, 9046, 7293, 5147, 1260, 1386, 6193, 4135, 3611,
      8583, 1446, 3480, 2022, 961, 7123, 7262, 2261, 8380, 2123, 1286, 1274, 1369, 831,  927,  993,  4484, 4865, 8473, 8587, 4200, 1216,
  };
  algorithms::Binary_Heap<int> min_heap(static_cast<int>(data_set.size()));
  algorithms::Binary_Heap<int> max_heap(static_cast<int>(data_set.size()));
  std::vector<int> sorted_data;
  sorted_data.reserve(data_set.size());
  for (auto const& data : data_set) {
    min_heap.insert(data);
    max_heap.insert(-1 * data);
    sorted_data.emplace_back(data);
    std::sort(sorted_data.begin(), sorted_data.end());
    ASSERT_EQ(min_heap.get_min().value(), sorted_data.at(0));
    auto last_value = sorted_data.end();
    --last_value;
    ASSERT_EQ(-1 * max_heap.get_min().value(), *last_value);
  }
}

TEST(MedianHeapsTest, Basic00) {
  static constexpr int heap_capacity{7};
  algorithms::Median_Heaps<int> median_heaps(heap_capacity);
  ASSERT_EQ(median_heaps.min_heap_capacity(), 4);
  ASSERT_EQ(median_heaps.max_heap_capacity(), 5);
  ASSERT_EQ(median_heaps.min_heap_size(), 0);
  ASSERT_EQ(median_heaps.max_heap_size(), 0);
  median_heaps.insert(1);
  ASSERT_EQ(median_heaps.min_heap_size(), 0);
  ASSERT_EQ(median_heaps.max_heap_size(), 1);
  ASSERT_EQ(median_heaps.compute_median(), 1);
  median_heaps.insert(3);
  ASSERT_EQ(median_heaps.compute_median(), 1);
  median_heaps.insert(-2);
  ASSERT_EQ(median_heaps.compute_median(), 1);
  median_heaps.insert(2);
  ASSERT_EQ(median_heaps.compute_median(), 1);
  median_heaps.insert(10);
  ASSERT_EQ(median_heaps.compute_median(), 2);
  median_heaps.insert(-5);
  ASSERT_EQ(median_heaps.compute_median(), 1);
  median_heaps.insert(-25);
  ASSERT_EQ(median_heaps.compute_median(), 1);
  ASSERT_EQ(median_heaps.min_heap_capacity(), 4);
  ASSERT_EQ(median_heaps.max_heap_capacity(), 5);
  ASSERT_EQ(median_heaps.min_heap_size(), 3);
  ASSERT_EQ(median_heaps.max_heap_size(), 4);
}

TEST(MedianHeapsTest, Basic01) {
  std::array data_set{
      6331, 2793, 1640, 9290, 225, 625,  6195, 2303, 5685, 1354, 4292, 7600, 6447, 4479, 9046, 7293, 5147, 1260, 1386, 6193, 4135, 3611,
      8583, 1446, 3480, 2022, 961, 7123, 7262, 2261, 8380, 2123, 1286, 1274, 1369, 831,  927,  993,  4484, 4865, 8473, 8587, 4200, 1216,
  };
  algorithms::Median_Heaps<int> median_heaps(data_set.size());
  std::vector<int> sorted_data;
  sorted_data.reserve(data_set.size());
  int median_sum{0};
  int true_median_sum{0};
  for (auto data : data_set) {
    median_heaps.insert(data);
    sorted_data.emplace_back(data);
    std::sort(sorted_data.begin(), sorted_data.end());
    int m_k = median_heaps.compute_median();
    int true_m_k = get_median(sorted_data);
    ASSERT_EQ(m_k, true_m_k);
    median_sum += m_k;
    true_median_sum += true_m_k;
  }
  ASSERT_EQ(median_sum, true_median_sum);
}

}  // namespace

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
