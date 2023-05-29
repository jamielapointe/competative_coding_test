
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <memory>
#include <numeric>
#include <queue>
#include <ranges>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace algorithms {
namespace prims_minimum_spanning_tree {

struct Node {
  using Key_T = int64_t;

  Key_T id{0};

  Key_T key() const { return id; }

  friend std::ostream &operator<<(std::ostream &os, Node const &node) {
    os << "Node ID " << node.id;
    return os;
  }

  bool operator==(Node const &other) const { return this->id == other.id; }
  bool operator!=(Node const &other) const { return !(other == *this); }
};

struct Edge {
  using Weight_T = int64_t;
  static constexpr int64_t kInfiniteWeight{1000000000};
  Node::Key_T head{0};
  Node::Key_T tail{0};
  Weight_T weight{0};
};

class Unordered_Graph {
 public:
  using Adjacency_Value = std::vector<Edge>;
  using Adjacency_List = std::unordered_map<Node::Key_T, Adjacency_Value>;
  using Node_Map = std::unordered_map<Node::Key_T, Node>;

  explicit Unordered_Graph(int64_t number_nodes, int64_t number_edges) : node_map_{}, adjacency_list_{} {
    node_map_.reserve(static_cast<std::size_t>(number_nodes));
    adjacency_list_.reserve(static_cast<std::size_t>(number_edges));
  }
  Unordered_Graph() = default;

  Adjacency_List const &adjacency_list() const { return adjacency_list_; }
  int64_t number_of_nodes() const { return static_cast<int64_t>(node_map_.size()); }

  Adjacency_Value &get_edge_nodes(Node::Key_T node_key) {
    auto node_it = adjacency_list_.find(node_key);
    if (node_it != adjacency_list_.end()) {
      return node_it->second;
    }
    throw std::logic_error("Node" + std::to_string(node_key) + " not found");
  }

  Node &get_node(Node::Key_T node_key) {
    auto node_it = node_map_.find(node_key);
    if (node_it != node_map_.end()) {
      return node_it->second;
    }
    throw std::logic_error("Node" + std::to_string(node_key) + " not found");
  }

  Node const &get_node(Node::Key_T node_key) const {
    auto node_it = node_map_.find(node_key);
    if (node_it != node_map_.end()) {
      return node_it->second;
    }
    throw std::logic_error("Node" + std::to_string(node_key) + " not found");
  }

  void add_edge(Node node0, Node node1, Edge::Weight_T weight) {
    node_map_[node0.key()] = node0;
    node_map_[node1.key()] = node1;
    adjacency_list_[node0.key()].emplace_back(node0.key(), node1.key(), weight);
    adjacency_list_[node1.key()].emplace_back(node1.key(), node0.key(), weight);
  }

  void add_edge(Node &&node0, Node &&node1, Edge::Weight_T weight) {
    node_map_[node0.key()] = node0;
    node_map_[node1.key()] = node1;
    adjacency_list_[node0.key()].emplace_back(node0.key(), node1.key(), weight);
    adjacency_list_[node1.key()].emplace_back(node1.key(), node0.key(), weight);
  }

 private:
  Node_Map node_map_;
  Adjacency_List adjacency_list_;
};

struct Vertex_Weight {
  Node::Key_T node_key{0};
  Edge::Weight_T weight{0};

  friend bool operator==(Vertex_Weight lhs, Vertex_Weight rhs) { return rhs.weight == lhs.weight && rhs.node_key == lhs.node_key; }
  friend bool operator!=(Vertex_Weight lhs, Vertex_Weight rhs) { return !(lhs == rhs); }
  friend bool operator<(Vertex_Weight lhs, Vertex_Weight rhs) {
    return lhs.weight < rhs.weight ? true : (rhs.weight < lhs.weight ? false : lhs.node_key < rhs.node_key);
  }
  friend bool operator<=(Vertex_Weight lhs, Vertex_Weight rhs) { return !(rhs < lhs); }
  friend bool operator>(Vertex_Weight lhs, Vertex_Weight rhs) { return rhs < lhs; }
  friend bool operator>=(Vertex_Weight lhs, Vertex_Weight rhs) { return !(lhs < rhs); }
};

inline int64_t prims_min_mst(Unordered_Graph const &graph) {
  // store vertices in a heap data structure for optimized min lookup
  std::priority_queue<Vertex_Weight, std::vector<Vertex_Weight>, std::greater<Vertex_Weight>> heap;

  Node::Key_T start_key{0};  // take a random vertex - start with vertex 0 as the source

  // ensure empty preallocated distances - initialized with infinite weight
  std::vector<bool> is_mst(static_cast<std::size_t>(graph.number_of_nodes()), false);
  std::vector<Edge::Weight_T> mst_weights(static_cast<std::size_t>(graph.number_of_nodes()), 0);
  std::vector<Edge::Weight_T> cost(static_cast<std::size_t>(graph.number_of_nodes()), Edge::kInfiniteWeight);

  // add the source node to the heap and set its weight to 0
  heap.push({.node_key = start_key, .weight = 0});
  cost.at(static_cast<std::size_t>(start_key)) = 0;

  while (!heap.empty()) {
    // extract the minimum weight vertex
    auto head_vertex_key = heap.top().node_key;
    heap.pop();

    // Different key values for the same vertex may exist in the heap.
    // the minimum key value (i.e., least weight) is processed first.
    // Thus, ignore the rest
    if (is_mst.at(static_cast<std::size_t>(head_vertex_key))) {
      continue;
    }

    is_mst.at(static_cast<std::size_t>(head_vertex_key)) = true;  // adds the vertex to the MST

    // iterate through all connected vertices
    for (auto const &neighbor : graph.adjacency_list().at(head_vertex_key)) {
      auto tail_vertex_key = neighbor.tail;
      auto weight = neighbor.weight;
      auto &tail_weight = cost.at(static_cast<std::size_t>(tail_vertex_key));
      // if tail is not in the MST and the weight of edge (head, tail) is smaller than the current key of tail,
      // then update its weight
      if (!is_mst.at(static_cast<std::size_t>(tail_vertex_key)) && tail_weight > weight) {
        tail_weight = weight;
        heap.push({.node_key = tail_vertex_key, .weight = tail_weight});
        mst_weights.at(static_cast<std::size_t>(tail_vertex_key)) = tail_weight;
      }
    }
  }

  return std::accumulate(mst_weights.begin(), mst_weights.end(), int64_t(0));
}

}  // namespace prims_minimum_spanning_tree
}  // namespace algorithms
