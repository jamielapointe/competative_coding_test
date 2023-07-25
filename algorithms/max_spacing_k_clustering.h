#include <algorithm>
#include <unordered_set>
#include <vector>

namespace algorithms {
namespace max_spacing_k_clustering {

template <typename Node_Value>
struct Node {
  using Node_Index = int64_t;
  Node_Index node_index;
  Node_Value node_value;
  friend bool operator==(Node const& lhs, Node const& rhs) { return lhs.node_index == rhs.node_index; }
  friend bool operator!=(Node const& lhs, Node const& rhs) { return !(lhs == rhs); }
};

template <typename Node_Value>
struct Edge {
  Node<Node_Value> node1;
  Node<Node_Value> node2;
  int64_t distance;
};

template <typename Node_Value>
class UnionFind {
 public:
  using Node = Node<Node_Value>;
  using Node_Index = typename Node::Node_Index;

  ///@brief Construct a new Union Find object
  ///
  ///@param number_of_nodes The number of nodes in the graph
  explicit UnionFind(Node_Index number_of_nodes) : parents_{}, rank_{} {
    parents_.reserve(static_cast<size_t>(number_of_nodes));
    rank_.reserve(static_cast<size_t>(number_of_nodes));
    for (Node_Index node_index = 0; node_index < number_of_nodes; ++node_index) {
      parents_.emplace_back(node_index, Node_Value(node_index));  // initialize the parent of each node to point to itself
      rank_.push_back(1);                                         // initialize the rank to 1
    }
  }

  ///@brief find a node whose parent is equal to itself
  ///
  /// Each time we follow a path, find a function and compress it further until the path length is greater than or equal to 1
  ///
  ///@param i Node to start search
  ///@return Node of node whose parent is equal to itself
  Node find(Node i) {
    // while we reach a node whose parent is equal to itself
    size_t index = static_cast<size_t>(i.node_index);
    while (parents_[index] != i) {
      parents_[index] = parents_[static_cast<size_t>(parents_[index].node_index)];  // skip a level
      i = parents_[index];                                                          // move to the next level
      index = static_cast<size_t>(i.node_index);
    }
    return i;
  }

  ///@brief  Union of the edge containing nodes i and j
  ///
  ///@param i node i
  ///@param j node j
  void merge(Node i, Node j) {
    auto s1 = find(i);
    auto s2 = find(j);
    auto s1_index = static_cast<size_t>(s1.node_index);
    auto s2_index = static_cast<size_t>(s2.node_index);
    if (s1_index != s2_index) {
      if (rank_[s1_index] < rank_[s2_index]) {
        parents_[s1_index] = s2;
      } else if (rank_[s1_index] > rank_[s2_index]) {
        parents_[s2_index] = s1;
      } else {
        parents_[s2_index] = s1;
        rank_[s1_index] += 1;
      }
    }
  }

  ///@brief  Determine if adding the two nodes of an edge would form a cycle
  ///
  ///@param i first node of an edge
  ///@param j second node of an edge
  ///@return true if adding the two nodes of an edge would from a cycle; otherwise, false
  bool is_cycle(Node i, Node j) { return find(i) == find(j); }

 private:
  std::vector<Node> parents_;
  std::vector<int64_t> rank_;
};

template <typename Node_Value>
inline int64_t max_spacing_k_clustering(std::vector<Edge<Node_Value>>& edges, int64_t num_nodes, int64_t k) {
  using Edge = Edge<Node_Value>;
  using UnionFind = UnionFind<Node_Value>;

  std::sort(edges.begin(), edges.end(), [](Edge& a, Edge& b) { return a.distance < b.distance; });

  UnionFind union_find(num_nodes);
  auto components = num_nodes;
  for (auto& edge : edges) {
    if (!union_find.is_cycle(edge.node1, edge.node2)) {
      if (components == k) {
        return edge.distance;
      }
      union_find.merge(edge.node1, edge.node2);
      --components;
    }
  }

  return -1;
}

}  // namespace max_spacing_k_clustering
}  // namespace algorithms
