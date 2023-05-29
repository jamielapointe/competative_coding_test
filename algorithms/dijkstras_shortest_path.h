
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <memory>
#include <queue>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

namespace algorithms {
namespace dijkstra_shortest_path {

struct Node {
  using Key_T = int64_t;

  bool is_visited{false};
  Key_T id{0};
  std::string label{};

  Key_T key() const { return id; }

  friend std::ostream &operator<<(std::ostream &os, Node const &node) {
    os << "Node ID " << node.id << " - " << node.label;
    return os;
  }

  bool operator==(Node const &other) const { return this->id == other.id; }
  bool operator!=(Node const &other) const { return !(other == *this); }
};

struct Edge {
  using Weight_T = int32_t;
  static constexpr Weight_T kInfiniteWeight{1000000};  //{std::numeric_limits<Edge::Weight_T>::max()};
  Node::Key_T head{0};
  Node::Key_T tail{0};
  Weight_T weight{0};
};

class Unordered_Graph {
 public:
  using Adjacency_Value = std::vector<Edge>;
  using Adjacency_List = std::unordered_map<Node::Key_T, Adjacency_Value>;
  using Node_Map = std::unordered_map<Node::Key_T, Node>;

  explicit Unordered_Graph(std::size_t default_size) : node_map_(default_size), adjacency_list_(default_size) {}
  Unordered_Graph() = default;

  Adjacency_List const &adjacency_list() const { return adjacency_list_; }
  int number_of_nodes() const { return static_cast<int>(node_map_.size()); }

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

struct Vertex_Distance {
  // Vertex_Distance(Node::Key_T node_in, Edge::Weight_T distance_in) :
  // node_key{node_in}, distance{distance_in} {}
  Node::Key_T node_key{0};
  Edge::Weight_T distance{0};

  friend bool operator==(Vertex_Distance lhs, Vertex_Distance rhs) { return rhs.distance == lhs.distance && rhs.node_key == lhs.node_key; }
  friend bool operator!=(Vertex_Distance lhs, Vertex_Distance rhs) { return !(lhs == rhs); }
  friend bool operator<(Vertex_Distance lhs, Vertex_Distance rhs) {
    return lhs.distance < rhs.distance ? true : (rhs.distance < lhs.distance ? false : lhs.node_key < rhs.node_key);
  }
  friend bool operator<=(Vertex_Distance lhs, Vertex_Distance rhs) { return !(rhs < lhs); }
  friend bool operator>(Vertex_Distance lhs, Vertex_Distance rhs) { return rhs < lhs; }
  friend bool operator>=(Vertex_Distance lhs, Vertex_Distance rhs) { return !(lhs < rhs); }
};

inline std::vector<Edge::Weight_T> dijkstra(Unordered_Graph &graph, Node::Key_T start_node_key) {
  // store vertices in a heap data structure for optimized min lookup
  std::priority_queue<Vertex_Distance, std::vector<Vertex_Distance>, std::greater<Vertex_Distance>> heap;

  // ensure empty preallocated distances
  std::vector<Edge::Weight_T> distances(static_cast<std::size_t>(graph.number_of_nodes()), Edge::kInfiniteWeight);

  // add the source node
  heap.push({.node_key = start_node_key, .distance = 0});
  distances.at(static_cast<std::size_t>(start_node_key)) = 0;

  while (!heap.empty()) {
    // extract the minimum distance vertex
    auto heap_node = heap.top();
    auto heap_node_key = heap_node.node_key;
    auto heap_node_distance = distances.at(static_cast<std::size_t>(heap_node_key));
    heap.pop();

    // iterate through all connected vertices of the min_distance_vertex
    // and relax them
    for (auto const &neighbor : graph.adjacency_list().at(heap_node_key)) {
      auto vertex = neighbor.tail;
      auto weight = neighbor.weight;

      // check if the distance to the neighbor can be shortened by going through
      // min_distance_vertex
      if (distances.at(static_cast<std::size_t>(vertex)) > heap_node_distance + weight) {
        distances.at(static_cast<std::size_t>(vertex)) = heap_node_distance + weight;
        heap.push({.node_key = vertex, .distance = distances.at(static_cast<std::size_t>(vertex))});
      }
    }
  }
  return distances;
}

}  // namespace dijkstra_shortest_path
}  // namespace algorithms
