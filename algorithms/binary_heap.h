#include <iostream>
#include <vector>

template <typename T>
class Binary_Heap {
 public:
  static constexpr int kDefaultCapacity{100};
  static constexpr int kArraySizeBuffer{10};

  explicit Binary_Heap(int capacity = kDefaultCapacity);
  explicit Binary_Heap(const std::vector<T>& items);

  bool is_empty() const;
  const T& get_min() const;

  void insert(const T& new_item);
  void delete_min();
  void delete_min(T& min_item);

 private:
  std::vector<T> array_;
  int current_size_{kDefaultCapacity};

  void build_heap();
  void percolate_down(int hole);
};

template <typename T>
Binary_Heap<T>::Binary_Heap(int capacity) : array_(static_cast<std::size_t>(capacity + 1)) {}

template <typename T>
Binary_Heap<T>::Binary_Heap(const std::vector<T>& items) : array_(items.size() + kArraySizeBuffer), current_size_(items.size()) {
  for (int i = 0; i < items.size(); i++) {
    array_[i + 1] = items[i];
  }
  build_heap();
}

template <typename T>
bool Binary_Heap<T>::is_empty() const {
  return current_size_ == 0;
}

template <typename T>
const T& Binary_Heap<T>::get_min() const {
  return array_[1];
}

template <typename T>
void Binary_Heap<T>::insert(const T& new_item) {
  if (current_size_ == static_cast<int>(array_.size()) - 1) {
    array_.resize(array_.size() * 2);
  }

  // Percolate up
  int hole = ++current_size_;
  for (; hole > 1 && new_item < array_[static_cast<std::size_t>(hole / 2)]; hole /= 2) {
    array_[static_cast<std::size_t>(hole)] = array_[static_cast<std::size_t>(hole / 2)];
  }
  array_[static_cast<std::size_t>(hole)] = new_item;
}

template <typename T>
void Binary_Heap<T>::delete_min() {
  if (is_empty()) {
    std::cout << "Heap is empty" << std::endl;
    return;
  }

  array_[1] = array_[static_cast<std::size_t>(current_size_--)];
  percolate_down(1);
}

template <typename T>
void Binary_Heap<T>::delete_min(T& min_item) {
  if (is_empty()) {
    std::cout << "Heap is empty" << std::endl;
    return;
  }

  min_item = array_[1];
  array_[1] = array_[current_size_--];
  percolate_down(1);
}

template <typename T>
void Binary_Heap<T>::build_heap() {
  for (int i = current_size_ / 2; i > 0; i--) {
    percolate_down(i);
  }
}

template <typename T>
void Binary_Heap<T>::percolate_down(int hole) {
  T temp = array_[static_cast<std::size_t>(hole)];
  int child = 2 * hole;
  for (; child <= current_size_; hole = child, child = hole * 2) {
    if (child + 1 <= current_size_ && array_[static_cast<std::size_t>(child + 1)] < array_[static_cast<std::size_t>(child)]) {
      ++child;
    }
    if (array_[static_cast<std::size_t>(child)] < temp) {
      array_[static_cast<std::size_t>(hole)] = array_[static_cast<std::size_t>(child)];
    } else {
      break;
    }
  }
  array_[static_cast<std::size_t>(hole)] = temp;
}
