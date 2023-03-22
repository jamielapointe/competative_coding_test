#pragma once

#include <iostream>
#include <optional>
#include <vector>

#include "utilities.h"

namespace algorithms {

template <typename T>
class Binary_Heap {
 public:
  using Index = int;

  Binary_Heap() = default;
  explicit Binary_Heap(int capacity);
  explicit Binary_Heap(const std::vector<T>& items);

  bool is_empty() const;
  bool is_full() const;
  const std::optional<T> get_min() const;

  int capacity() const { return static_cast<int>(array_.capacity()); }
  int size() const { return static_cast<int>(array_.size()); }

  void insert(const T& new_item);
  void delete_min();

  // Parse binary tree
  const T get_node(Index i) { return array_.at(i); }
  Index parent_index(Index node_index) { return (node_index - 1) / 2; }
  Index left_child_index(Index node_index) { return 2 * node_index + 1; }
  Index right_child_index(Index node_index) { return 2 * node_index + 2; }

 private:
  std::vector<T> array_;

  void build_heap(int node_index);
};

template <typename T>
Binary_Heap<T>::Binary_Heap(int capacity) : array_{} {
  if (capacity > 0) {
    array_.reserve(static_cast<std::size_t>(capacity));
  }
}

template <typename T>
Binary_Heap<T>::Binary_Heap(const std::vector<T>& items) : array_(items) {
  build_heap(0);
}

template <typename T>
bool Binary_Heap<T>::is_empty() const {
  return size() == 0;
}

template <typename T>
bool Binary_Heap<T>::is_full() const {
  return size() == capacity();
}

template <typename T>
const std::optional<T> Binary_Heap<T>::get_min() const {
  if (!is_empty()) {
    return array_[0];
  }
  return {};
}

template <typename T>
void Binary_Heap<T>::insert(const T& new_item) {
  if (is_full()) {
    int new_capacity = capacity() * 2;
    std::cout << "Binary Heap is full!\n";
    std::cout << "Current capacity == " << capacity() << "; new capacity == " << new_capacity << "\n";
    array_.reserve(static_cast<std::size_t>(new_capacity));
  }

  // insert at the end
  array_.emplace_back(new_item);

  // fix the heap property
  Index i = size() - 1;
  while (i != 0 && array_[static_cast<std::size_t>(parent_index(i))] > array_.at(static_cast<std::size_t>(i))) {
    swap(array_, i, parent_index(i));
    i = parent_index(i);
  }
}

template <typename T>
void Binary_Heap<T>::delete_min() {
  if (is_empty()) {
    std::cout << "Heap is empty" << std::endl;
    return;
  }

  array_[0] = array_[array_.size() - 1];
  array_.erase(array_.end() - 1);
  build_heap(0);
}

template <typename T>
void Binary_Heap<T>::build_heap(int node_index) {
  Index l_index = left_child_index(node_index);
  Index r_index = right_child_index(node_index);
  Index smallest_index = node_index;
  if (l_index < size() && array_.at(static_cast<size_t>(l_index)) < array_.at(static_cast<size_t>(smallest_index))) {
    smallest_index = l_index;
  }
  if (r_index < size() && array_.at(static_cast<size_t>(r_index)) < array_.at(static_cast<size_t>(smallest_index))) {
    smallest_index = r_index;
  }
  if (smallest_index != node_index) {
    ::algorithms::swap(array_, node_index, smallest_index);
    build_heap(smallest_index);
  }
}

}  // namespace algorithms
