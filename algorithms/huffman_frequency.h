///\file huffman_codes.h
///\author Jamie LaPointe (jamie.lapointe@gmail.com)
///\brief Implement Huffman Codes Greedy Algorithm
///\version 0.1
///\date 2023-09-17
///
///@copyright Copyright (c) 2023
///

#pragma once

#include <memory>
#include <numeric>
#include <queue>
#include <unordered_map>
#include <vector>

namespace algorithms {

class HuffmanFrequencyTable {
 public:
  struct BinaryTreeNode {
    int data{0};
    int frequency{0};
    BinaryTreeNode* left{nullptr};
    BinaryTreeNode* right{nullptr};

    BinaryTreeNode(int data_in, int frequency_in) : data{data_in}, frequency{frequency_in} {}

    auto operator<=>(const BinaryTreeNode& other) const noexcept { return frequency <=> other.frequency; }
    bool operator==(const BinaryTreeNode& other) const noexcept { return data == other.data && frequency == other.frequency; }
  };

  using NodeMinHeap = std::priority_queue<BinaryTreeNode, std::vector<BinaryTreeNode>, std::greater<BinaryTreeNode>>;

  struct BinaryTreeNodeHash {
    std::size_t operator()(const BinaryTreeNode& node) const noexcept { return std::hash<int>{}(node.data) ^ std::hash<int>{}(node.frequency); }
  };

  struct MinMaxCodeLength {
    int min{std::numeric_limits<int>::max()};
    int max{std::numeric_limits<int>::min()};
  };

  explicit HuffmanFrequencyTable(NodeMinHeap& frequency_min_heap) { generate_tree(frequency_min_heap); }

  void generate_tree(NodeMinHeap& frequency_min_heap) {
    int index = static_cast<int>(frequency_min_heap.size());
    while (frequency_min_heap.size() > 1) {
      auto left = new BinaryTreeNode(frequency_min_heap.top());
      frequency_min_heap.pop();
      auto right = new BinaryTreeNode(frequency_min_heap.top());
      frequency_min_heap.pop();
      index += (left->data + right->data);
      auto parent = new BinaryTreeNode(index, left->frequency + right->frequency);
      parent->left = left;
      parent->right = right;
      frequency_min_heap.push(*parent);
    }
    root_ = frequency_min_heap.top();
    frequency_min_heap.pop();
  }

  MinMaxCodeLength get_min_max_code_length() {
    MinMaxCodeLength min_max_code_length;
    std::unordered_map<BinaryTreeNode, int, BinaryTreeNodeHash> node_depth_map;
    std::queue<BinaryTreeNode> node_queue;
    node_queue.push(root_);
    node_depth_map[root_] = 0;
    while (!node_queue.empty()) {
      auto node = node_queue.front();
      node_queue.pop();
      if (is_leaf(node)) {
        if (node_depth_map[node] > min_max_code_length.max) {
          min_max_code_length.max = node_depth_map[node];
        }
        if (node_depth_map[node] < min_max_code_length.min) {
          min_max_code_length.min = node_depth_map[node];
        }
      } else {
        if (node.left != nullptr) {
          auto left = *node.left;
          node_queue.push(left);
          node_depth_map[left] = node_depth_map[node] + 1;
        }
        if (node.right != nullptr) {
          auto right = *node.right;
          node_queue.push(right);
          node_depth_map[right] = node_depth_map[node] + 1;
        }
      }
    }
    return min_max_code_length;
  }

 private:
  BinaryTreeNode root_{-1, -1};

  bool is_leaf(BinaryTreeNode const& node) { return node.left == nullptr && node.right == nullptr; }
};

}  // namespace algorithms
