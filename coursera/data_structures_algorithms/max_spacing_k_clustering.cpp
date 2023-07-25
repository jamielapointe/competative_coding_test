#include "max_spacing_k_clustering.h"

#include <cassert>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "config.h"

using namespace std;
using namespace algorithms::max_spacing_k_clustering;

class Coursera_Max_Spacing_K_Clustering {
 public:
  using Node_Value = int64_t;
  using Node = Node<Node_Value>;
  using Edge = Edge<Node_Value>;
  using UnionFind = UnionFind<Node_Value>;

  explicit Coursera_Max_Spacing_K_Clustering(int64_t k_in) : k_(k_in) {}
  Coursera_Max_Spacing_K_Clustering() = delete;

  void process_data_question_one(string_view fname) {
    ifstream data_file(fname.data());
    string line;
    // allow the counting of new line characters
    data_file.unsetf(std::ios_base::skipws);
    // count the new lines with a C++ STL algorithm
    auto number_of_edges = std::count(std::istream_iterator<char>(data_file), std::istream_iterator<char>(), '\n');
    edges_.reserve(static_cast<size_t>(number_of_edges));
    // Clear EOF && reset file pointer to 0
    data_file.clear();   // clear the EOF flag
    data_file.seekg(0);  // go to start of file
    assert(data_file.is_open());
    assert(data_file.good());
    // first grab the number of nodes
    getline(data_file, line);
    istringstream ss(line);
    ss >> number_of_nodes_;
    while (getline(data_file, line)) {
      istringstream ss1(line);
      int64_t head_node_key{0};
      int64_t tail_node_key{0};
      int64_t distance{0};
      ss1 >> head_node_key;
      --head_node_key;  // switch from 1 to 0 base indexing
      ss1 >> tail_node_key;
      --tail_node_key;  // switch from 1 to 0 base indexing
      ss1 >> distance;
      Node node1{.node_index = head_node_key, .node_value = head_node_key};
      Node node2{.node_index = tail_node_key, .node_value = tail_node_key};
      edges_.emplace_back(node1, node2, distance);
    }
  }

  int64_t get_max_spacing_k_clustering() { return max_spacing_k_clustering(edges_, number_of_nodes_, k_); }

 private:
  int64_t k_{1};
  int64_t number_of_nodes_{0};
  std::vector<Edge> edges_;
};

class Coursera_Min_Spacing_Max_K_Clustering {
 public:
  using Node_Value = std::string;
  using Node = Node<Node_Value>;
  using Node_Index = Node::Node_Index;
  using Edge = Edge<Node_Value>;
  using Union_Find = UnionFind<Node_Value>;

  explicit Coursera_Min_Spacing_Max_K_Clustering(int64_t min_spacing_in) : min_spacing_{min_spacing_in} {}
  Coursera_Min_Spacing_Max_K_Clustering() = delete;

  void process_data_question_two(string_view fname) {
    ifstream data_file(fname.data());
    string line;

    // the first line contains the number of nodes and bits
    getline(data_file, line);
    istringstream ss(line);
    ss >> number_of_nodes_;
    ss >> number_of_bits_;

    // get the rest of the lines
    std::string bit_string = "000000000000000000000000";
    assert(bit_string.length() == static_cast<size_t>(number_of_bits_));
    nodes_.reserve(static_cast<size_t>(number_of_nodes_));
    Node_Index node_index{0};
    while (getline(data_file, line)) {
      istringstream ss1(line);
      for (int i = 0; i < number_of_bits_; ++i) {
        ss1 >> bit_string[static_cast<size_t>(i)];
      }
      nodes_.emplace_back(node_index, bit_string);
      ++node_index;
    }
  }

  int64_t max_clusters() {
    std::unordered_map<Node_Value, Node_Value> parent_map;
    for (Node node : nodes_) {
      parent_map[node.node_value] = node.node_value;
    }
    int64_t max_k = static_cast<int64_t>(parent_map.size());
    for (Node node : nodes_) {
      // find a node whose parent is equal to itself
      auto node_parent = parent_map[node.node_value];
      while (parent_map[node_parent] != node_parent) {
        node_parent = parent_map[node_parent];
      }
      // loop through bit strings similar to the current node
      for (auto similar_bit_string : similar(node.node_value)) {
        if (parent_map.find(similar_bit_string) != parent_map.end()) {
          // find a node whose parent is equal to itself
          auto parent = parent_map[similar_bit_string];
          while (parent_map[parent] != parent) {
            parent = parent_map[parent];
          }
          if (node_parent != parent) {
            parent_map[parent] = node_parent;
            --max_k;
          }
        }
      }
    }
    return max_k;
  }

 private:
  int64_t number_of_nodes_{0};
  int64_t number_of_bits_{0};
  int64_t min_spacing_{1};
  std::vector<Node> nodes_;
  std::vector<Edge> edges_;

  int64_t compute_hamming_distance(Node node1, Node node2) {
    int64_t distance{0};
    for (int64_t i = 0; i < number_of_bits_; ++i) {
      if (distance >= min_spacing_) {
        distance = min_spacing_ + 1;
        break;
      }
      if (node1.node_value[static_cast<size_t>(i)] != node2.node_value[static_cast<size_t>(i)]) {
        ++distance;
      }
    }
    return distance;
  }

  char invert_bit(char bit) { return bit == '0' ? '1' : '0'; }

  std::vector<Node_Value> similar(Node_Value v) {
    std::vector<Node_Value> result;
    static const int64_t num_similar{number_of_bits_ * (number_of_bits_ + 1) / 2};
    result.reserve(static_cast<size_t>(num_similar));
    for (size_t i = 0; i < static_cast<size_t>(number_of_bits_); ++i) {
      std::string bit0 = v.substr(0, i) + invert_bit(v[i]) + v.substr(i + 1, v.length() - i - 1);
      result.push_back(bit0);
      assert(bit0.length() == static_cast<size_t>(number_of_bits_));
      for (size_t j = i + 1; j < static_cast<size_t>(number_of_bits_); ++j) {
        std::string bit1 = v.substr(0, i) + invert_bit(v[i]) + v.substr(i + 1, j - (i + 1)) + invert_bit(v[j]) + v.substr(j + 1, v.length() - j - 1);
        result.push_back(bit1);
        assert(bit1.length() == static_cast<size_t>(number_of_bits_));
      }
    }
    return result;
  }
};

static int64_t run_question_one(string_view full_path, int64_t k) {
  Coursera_Max_Spacing_K_Clustering coursera(k);
  coursera.process_data_question_one(full_path);
  return coursera.get_max_spacing_k_clustering();
}

static int64_t run_question_two(string_view full_path, int64_t min_spacing) {
  Coursera_Min_Spacing_Max_K_Clustering coursera(min_spacing);
  coursera.process_data_question_two(full_path);
  return coursera.max_clusters();
}

static void run_coursera() {
  cout << "Coursera Quiz - Course 2 Week 4"
       << "\n";

  string const base_dir(EXECUTABLE_BASE_DIR);
  string const fname("/data/clustering1.txt");
  string const full_path = base_dir + fname;
  static constexpr int64_t k{4};
  auto min_distance = run_question_one(full_path, k);
  cout << "The answer to #1 - min distance: " << min_distance << "\n";

  string const fname2("/data/clustering_big.txt");
  string const full_path2 = base_dir + fname2;
  static constexpr int64_t min_spacing{3};
  auto max_k = run_question_two(full_path2, min_spacing);
  cout << "The answer to #2 - max k: " << max_k << "\n";
}

int main() {
  run_coursera();

  return 0;
}
