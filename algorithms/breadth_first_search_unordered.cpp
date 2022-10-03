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

using std::find_if;

struct Node {
  using Key_T = uint32_t;

  bool is_visited{false};
  uint32_t id{0};
  std::string label{};

  Node(bool is_visited_in, uint32_t id_in, std::string label_in)
      : is_visited{is_visited_in}, id{id_in}, label{label_in} {}

  Key_T key() const { return id; }
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
    throw std::logic_error("Node not found");
  }

  void add_edge(Node_Pointer node0, Node_Pointer node1) {
    adjacency_list_[node0->key()].push_back(node1);
    adjacency_list_[node1->key()].push_back(node0);
  }

 private:
  Adjacency_List adjacency_list_;
};

static void bfs(
    Unordered_Graph& graph, Unordered_Graph::Node_Pointer& start_node,
    std::function<void(Unordered_Graph::Node_Pointer&)> callback = nullptr) {
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
    } catch (std::logic_error exc) {
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

static void print_node(Unordered_Graph::Node_Pointer& node) {
  std::cout << "Node ID " << node->id << " - " << node->label << std::endl;
}

int main() {
  static constexpr uint32_t nodeid0{0};
  static constexpr uint32_t nodeid1{1};
  static constexpr uint32_t nodeid2{2};
  static constexpr uint32_t nodeid3{3};
  static constexpr uint32_t nodeid4{4};
  static constexpr uint32_t nodeid5{5};
  static constexpr uint32_t nodeid6{6};
  static constexpr uint32_t nodeid7{7};
  static constexpr uint32_t nodeid8{8};
  static constexpr uint32_t nodeid9{9};

  Unordered_Graph graph;
  auto node0 = std::make_shared<Node>(false, nodeid0, "Frankfurt");
  auto node1 = std::make_shared<Node>(false, nodeid1, "Mannheim");
  auto node2 = std::make_shared<Node>(false, nodeid2, "Würzburg");
  auto node3 = std::make_shared<Node>(false, nodeid3, "Kassel");
  auto node4 = std::make_shared<Node>(false, nodeid4, "Karlsruhe");
  auto node5 = std::make_shared<Node>(false, nodeid5, "Nürnberg");
  auto node6 = std::make_shared<Node>(false, nodeid6, "Erfurt");
  auto node7 = std::make_shared<Node>(false, nodeid7, "München");
  auto node8 = std::make_shared<Node>(false, nodeid8, "Augsburg");
  auto node9 = std::make_shared<Node>(false, nodeid9, "Stuttgart");

  graph.add_edge(node0, node1);
  graph.add_edge(node0, node2);
  graph.add_edge(node0, node3);
  graph.add_edge(node1, node4);
  graph.add_edge(node2, node5);
  graph.add_edge(node2, node6);
  graph.add_edge(node3, node7);
  graph.add_edge(node4, node8);
  graph.add_edge(node5, node9);

  bfs(graph, node0, print_node);
}
