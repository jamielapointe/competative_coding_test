
#include <array>
#include <iostream>
#include <limits>
#include <vector>

namespace algorithms {

struct Node {
  int key{0};
  int frequency{0};

  friend std::ostream& operator<<(std::ostream& os, Node const& node) {
    os << node.key << " - " << node.frequency;
    return os;
  }
};

struct BinaryTree {
  Node node{};
  BinaryTree* left{nullptr};
  BinaryTree* right{nullptr};
};

struct OptimalSearchTreeResult {
  int cost{0};
  BinaryTree root{};
};

namespace internal {
template <typename T, size_t key_size>
BinaryTree* construct_tree(int i, int j, std::vector<std::vector<int>> const& root, std::array<T, key_size> const& keys) {
  if (i > j) {
    return nullptr;
  }
  int r = root[i][j];
  auto node = new BinaryTree();
  node->node.key = keys[r];
  node->left = construct_tree(i, r - 1, root, keys);
  node->right = construct_tree(r + 1, j, root, keys);
  return node;
}
}  // namespace internal

template <typename T, size_t key_size>
OptimalSearchTreeResult optimal_binary_search_tree(std::array<T, key_size> const& keys, std::array<T, key_size> const& frequencies) {
  int num_keys{static_cast<int>(key_size)};
  std::vector<T> cumulative_frequencies(num_keys + 1);
  std::vector<std::vector<T>> cost(num_keys + 1, std::vector<T>(num_keys + 1));
  std::vector<std::vector<int>> root(num_keys + 1, std::vector<int>(num_keys + 1));

  cumulative_frequencies[0] = frequencies[0];
  for (int i = 0; i < num_keys; ++i) {
    cumulative_frequencies[i] = cumulative_frequencies[i - 1] + frequencies[i];
  }
  cumulative_frequencies[key_size] = 0;

  // for (int i = 0; i < num_keys; ++i) {
  //   root[i][i] = i;
  //   cost[i][i] = 0;
  // }

  for (int len = 1; len <= num_keys; ++len) {
    for (int i = 0; i <= num_keys - len; ++i) {
      int j = i + len - 1;
      cost[i][j] = std::numeric_limits<int>::max();
      for (int r = i; r <= j; ++r) {
        auto c = ((r > i) ? cost[i][r - 1] : 0) + ((r < j) ? cost[r + 1][j] : 0) + cumulative_frequencies[j] - ((i > 0) ? cumulative_frequencies[i - 1] : 0);
        if (c < cost[i][j]) {
          cost[i][j] = c;
          root[i][j] = r;
        }
      }
    }
  }

  OptimalSearchTreeResult result;
  result.cost = cost[0][num_keys - 1];
  result.root = *internal::construct_tree(0, num_keys - 1, root, keys);
  return result;
}

}  // namespace algorithms
