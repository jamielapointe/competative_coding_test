
#include <cstdint>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace algorithms {
namespace scc_ordered {

/// \brief represent a node in a graph
/// This is a basic node with a flag to determine if it has been visited, along
/// with a unique id key and string label describing the node
struct Node {
  /// The key type
  using Key_T = uint32_t;

  /// has the node been visited by a search algorithm
  bool is_visited{false};
  /// the unique ID
  Key_T id{0};
  /// A label describing the node
  std::string label{0};

  /// construct a new node
  Node(bool is_visited_in, Key_T id_in, std::string label_in) : is_visited{is_visited_in}, id{id_in}, label{label_in} {}

  /// Return the key
  Key_T key() const { return id; }

  friend std::ostream& operator<<(std::ostream& os, Node const& node) {
    os << "Node ID " << node.id << " - " << node.label;
    return os;
  }

  bool operator==(Node const& other) const { return this->id == other.id; }
  bool operator!=(Node const& other) const { return !(other == *this); }
};

/// \brief Ordered Graph
class Ordered_Graph {
 public:
  using Node_Pointer = std::shared_ptr<Node>;
  using Node_List = std::vector<Node_Pointer>;
  using Adjacency_Value = std::list<Node_Pointer>;
  using Adjacency_List = std::unordered_map<uint32_t, Adjacency_Value>;

  Adjacency_List const& adjacency_list() const { return adjacency_list_; }

  bool const& is_direction_forward() const { return is_forward_; }

  Adjacency_Value* get_edge_nodes(Node::Key_T node_key) {
    auto node_it = adjacency_list_.find(node_key);
    if (node_it != adjacency_list_.end()) {
      return &node_it->second;
    }
    return nullptr;
  }

  void add_edge(Node_Pointer head_node, Node_Pointer tail_node) { adjacency_list_[head_node->key()].push_back(tail_node); }

  void transpose() { is_forward_ = !is_forward_; }

 private:
  Adjacency_List adjacency_list_;
  bool is_forward_{false};
};

inline void dfs(Ordered_Graph& graph, Ordered_Graph::Node_Pointer& start_node, std::function<void(Ordered_Graph::Node_Pointer&)> callback = nullptr) {
  start_node->is_visited = true;
  if (callback) {
    callback(start_node);
  }
  Ordered_Graph::Adjacency_Value* node_edges_ptr = graph.get_edge_nodes(start_node->key());
  if (node_edges_ptr == nullptr) {
    return;
  }
  for (auto& edge_node : *node_edges_ptr) {
    if (!edge_node->is_visited) {
      dfs(graph, edge_node, callback);
    }
  }
}

}  // namespace scc_ordered
}  // namespace algorithms
