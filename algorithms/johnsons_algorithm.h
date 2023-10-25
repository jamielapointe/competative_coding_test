
#include <compare>
#include <limits>
#include <memory>
#include <queue>
#include <unordered_map>
#include <vector>
namespace algorithms::johnsons_algorithm {

struct Node {
  bool is_visited{false};
  int id{0};

  bool operator==(Node const &other) const { return this->id == other.id; }
  bool operator!=(Node const &other) const { return !(other == *this); }
};

struct Edge {
  static constexpr int kInfiniteWeight{std::numeric_limits<int>::max()};
  int head_node_id{0};
  int tail_node_id{0};
  int weight{0};
};

struct NodeDistance {
  int node_id{0};
  int distance{0};
  auto operator<=>(NodeDistance const &other) const {
    return (other.distance == distance && other.node_id == node_id)
               ? std::strong_ordering::equal
               : (other.distance < distance   ? std::strong_ordering::less
                  : distance < other.distance ? std::strong_ordering::greater
                                              : (other.node_id < node_id ? std::strong_ordering::less : std::strong_ordering::greater));
  }
  auto operator==(NodeDistance const &other) const { return other.distance == distance && other.node_id == node_id; }
};

struct Directed_Graph {
  using NodeMap = std::unordered_map<int, Node>;
  using EdgeList = std::vector<Edge>;
  using NodeAdjacencyMap = std::unordered_map<int, EdgeList>;

  NodeMap node_map_{};
  NodeAdjacencyMap adjacency_map_{};

  Node empty_node_{};
  EdgeList empty_edge_list_{};

  Directed_Graph(int num_nodes, int num_edges) : node_map_(num_nodes), adjacency_map_(num_edges) {}

  Node &get_node(int node_id) {
    [[likely]] if (auto node_it = node_map_.find(node_id); node_it != node_map_.end()) { return node_it->second; }
    return empty_node_;
  }

  void add_edge(int head_node_id, int tail_node_id, int edge_cost) {
    if (!node_map_.contains(head_node_id)) {
      node_map_.emplace(head_node_id, Node{.id = head_node_id});
    }
    if (!node_map_.contains(tail_node_id)) {
      node_map_.emplace(tail_node_id, Node{.id = tail_node_id});
    }
    adjacency_map_[head_node_id].emplace_back(Edge{.head_node_id = head_node_id, .tail_node_id = tail_node_id, .weight = edge_cost});
  }

  EdgeList get_edges(int node_id) {
    [[likely]] if (auto edge_list_it = adjacency_map_.find(node_id); edge_list_it != adjacency_map_.end()) { return edge_list_it->second; }
    return empty_edge_list_;
  }
};

struct JohnsonsAlgorithmResult {
  bool is_valid{false};
  int shortest_path{std::numeric_limits<int>::max()};
};

void dijkstra_shortest_path(std::unique_ptr<Directed_Graph> &graph, int source_node_id, std::unordered_map<int, int> &shortest_path_map) {
  std::priority_queue<NodeDistance, std::vector<NodeDistance>, std::greater<NodeDistance>> node_distance_heap{};

  auto &start_node = graph->get_node(source_node_id);
  start_node.is_visited = true;
  shortest_path_map[start_node.id] = 0;
  node_distance_heap.push({.node_id = start_node.id, .distance = 0});

  while (!node_distance_heap.empty()) {
    auto head_node_id = node_distance_heap.top().node_id;
    node_distance_heap.pop();
    for (auto &node_edge : graph->get_edges(head_node_id)) {
      auto &tail_node = graph->get_node(node_edge.tail_node_id);
      if (!tail_node.is_visited) {
        tail_node.is_visited = true;
        shortest_path_map[tail_node.id] = shortest_path_map[head_node_id] + node_edge.weight;
        node_distance_heap.push({.node_id = tail_node.id, .distance = shortest_path_map[tail_node.id]});
      }
    }
  }
}

bool bellman_ford(int start_node, std::unique_ptr<Directed_Graph> &graph, std::unordered_map<int, int> &distance_map) {
  // initialize the distance map
  for (auto &node : graph->node_map_) {
    distance_map[node.first] = Edge::kInfiniteWeight;
  }
  distance_map[start_node] = 0;

  // relax edges repeatedly (n-1 times)
  auto num_nodes = graph->node_map_.size();
  for (int i = 0; i < num_nodes - 1; ++i) {
    for (auto &adj_map_item : graph->adjacency_map_) {
      for (auto &edge : adj_map_item.second) {
        auto head_node_id = edge.head_node_id;
        auto tail_node_id = edge.tail_node_id;
        auto edge_weight = edge.weight;
        if (distance_map[head_node_id] != Edge::kInfiniteWeight && distance_map[head_node_id] + edge_weight < distance_map[tail_node_id]) {
          distance_map[tail_node_id] = distance_map[head_node_id] + edge_weight;
        }
      }
    }
  }

  // check for negative-weight cycles
  for (auto &adj_map_item : graph->adjacency_map_) {
    for (auto &edge : adj_map_item.second) {
      auto head_node_id = edge.head_node_id;
      auto tail_node_id = edge.tail_node_id;
      auto edge_weight = edge.weight;
      if (distance_map[head_node_id] != Edge::kInfiniteWeight && distance_map[head_node_id] + edge_weight < distance_map[tail_node_id]) {
        return false;  // Graph contains a negative-weight cycle - abort
      }
    }
  }

  return true;
}

JohnsonsAlgorithmResult johnsons_algorithm(std::unique_ptr<Directed_Graph> &graph) {
  JohnsonsAlgorithmResult result;

  // add a new node to the graph with edges to all other nodes with weight 0
  auto num_nodes = graph->node_map_.size();
  auto num_edges = graph->adjacency_map_.size();
  auto new_node_id = num_nodes + 1;
  for (auto &node : graph->node_map_) {
    graph->add_edge(new_node_id, node.first, 0);
  }

  std::unordered_map<int, int> distance_map;
  if (!bellman_ford(new_node_id, graph, distance_map)) {
    // The graph contains a negative-weight cycle - thus this algorithm is invalid on it
    return result;
  }
  result.is_valid = true;

  // Create a new graph with re-weighted edges
  auto new_graph = std::make_unique<Directed_Graph>(num_nodes, num_edges);
  for (auto &adj_map_item : graph->adjacency_map_) {
    for (auto &edge : adj_map_item.second) {
      auto head_node_id = edge.head_node_id;
      auto tail_node_id = edge.tail_node_id;
      auto edge_weight = edge.weight;
      auto new_edge_weight = edge_weight + distance_map[head_node_id] - distance_map[tail_node_id];
      new_graph->add_edge(head_node_id, tail_node_id, new_edge_weight);
    }
  }

  // Initialize shortest path map
  std::unordered_map<int, std::unordered_map<int, int>> shortest_path_map;
  // Remove temporary node from the graph
  new_graph->node_map_.erase(new_node_id);
  new_graph->adjacency_map_.erase(new_node_id);

  // Run Dijkstra's algorithm on each node in the graph
  for (auto &node : new_graph->node_map_) {
    std::unordered_map<int, int> dijkstra_shortest_path_map;
    dijkstra_shortest_path(new_graph, node.first, dijkstra_shortest_path_map);
    shortest_path_map[node.first] = dijkstra_shortest_path_map;
  }

  // Re-weight the shortest paths
  for (auto &node_u : new_graph->node_map_) {
    for (auto &node_v : new_graph->node_map_) {
      shortest_path_map[node_u.first][node_v.first] += distance_map[node_v.first] - distance_map[node_u.first];
      if (shortest_path_map[node_u.first][node_v.first] < result.shortest_path) {
        result.shortest_path = shortest_path_map[node_u.first][node_v.first];
      }
    }
  }

  return result;
}

}  // namespace algorithms::johnsons_algorithm
