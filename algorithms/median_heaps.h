
#include "binary_heap.h"
#include "utilities.h"

namespace algorithms {

template <typename T>
class Median_Heaps {
 public:
  Median_Heaps() = default;
  explicit Median_Heaps(int capacity);

  void insert(T value);
  T compute_median() const;
  T get_max_value() const { return -1 * max_heap_.get_min().value(); }

  int min_heap_size() { return min_heap_.size(); }
  int min_heap_capacity() { return min_heap_.capacity(); }
  int max_heap_size() { return max_heap_.size(); }
  int max_heap_capacity() { return max_heap_.capacity(); }

 private:
  // min heap stores the larger elements
  Binary_Heap<T> min_heap_;
  // max heap stores the smaller elements
  Binary_Heap<T> max_heap_;

  constexpr int max_heap_capacity(int capacity) { return algorithms::is_even(capacity) ? capacity / 2 : (capacity + 1) / 2; }

  constexpr int min_heap_capacity(int capacity) { return capacity / 2; }

  void balance_heaps();
};

template <typename T>
Median_Heaps<T>::Median_Heaps(int capacity) : min_heap_(min_heap_capacity(capacity) + 1), max_heap_(max_heap_capacity(capacity) + 1) {}

template <typename T>
void Median_Heaps<T>::balance_heaps() {
  while (max_heap_.size() < min_heap_.size()) {
    max_heap_.insert(-1 * min_heap_.get_min().value());
    min_heap_.delete_min();
  }

  if (max_heap_.size() - min_heap_.size() > 1) {
    min_heap_.insert(get_max_value());
    max_heap_.delete_min();
  }
}

template <typename T>
void Median_Heaps<T>::insert(T value) {
  if (max_heap_.is_empty() || value < get_max_value()) {
    max_heap_.insert(-value);
  } else {
    min_heap_.insert(value);
  }
  balance_heaps();
}

template <typename T>
T Median_Heaps<T>::compute_median() const {
  return get_max_value();
}

}  // namespace algorithms
