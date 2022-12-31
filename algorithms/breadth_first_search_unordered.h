#include <algorithm>
#include <cstdint>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <queue>
#include <stdexcept>
#include <unordered_map>
#include <vector>

namespace algorithms {
namespace bfs_unordered {

using std::find_if;

struct Node {
  using Key_T = uint32_t;

  bool is_visited{false};
  uint32_t id{0};
  std::string label{};

  Node(bool is_visited_in, uint32_t id_in, std::string label_in) : is_visited{is_visited_in}, id{id_in}, label{label_in} {}

  Key_T key() const { return id; }

  friend std::ostream& operator<<(std::ostream& os, Node const& node) {
    os << "Node ID " << node.id << " - " << node.label;
    return os;
  }

  bool operator==(Node const& other) const { return this->id == other.id; }
  bool operator!=(Node const& other) const { return !(other == *this); }
};

class Unordered_Graph {
 public:
  using Node_Pointer = std::shared_ptr<Node>;
  using Node_List = std::vector<Node_Pointer>;
  using Adjacency_Value = std::list<Node_Pointer>;
  using Adjacency_List = std::unordered_map<uint32_t, Adjacency_Value>;

  Adjacency_List const& adjacency_list() const { return adjacency_list_; }

  Adjacency_Value& get_edge_nodes(Node::Key_T node_key) {
    auto node_it = adjacency_list_.find(node_key);
    if (node_it != adjacency_list_.end()) {
      return node_it->second;
    }
    throw std::logic_error("Node" + std::to_string(node_key) + " not found");
  }

  void add_edge(Node_Pointer node0, Node_Pointer node1) {
    adjacency_list_[node0->key()].push_back(node1);
    adjacency_list_[node1->key()].push_back(node0);
  }

 private:
  Adjacency_List adjacency_list_;
};

inline void bfs(Unordered_Graph& graph, Unordered_Graph::Node_Pointer& start_node, std::function<void(Unordered_Graph::Node_Pointer&)> callback = nullptr) {
  std::queue<Unordered_Graph::Node_Pointer> node_queue;
  start_node->is_visited = true;
  if (callback) {
    callback(start_node);
  }
  node_queue.push(start_node);
  while (!node_queue.empty()) {
    Node& node = *node_queue.front();
    node_queue.pop();
    Unordered_Graph::Adjacency_Value node_edges;
    try {
      node_edges = graph.get_edge_nodes(node.key());
    } catch (std::logic_error const& exc) {
      std::cerr << "Out of Range error: " << exc.what() << '\n';
      return;
    }
    for (auto& edge_node : node_edges) {
      if (!edge_node->is_visited) {
        edge_node->is_visited = true;
        if (callback) {
          callback(edge_node);
        }
        node_queue.push(edge_node);
      }
    }
  }
}

}  // namespace bfs_unordered
}  // namespace algorithms
