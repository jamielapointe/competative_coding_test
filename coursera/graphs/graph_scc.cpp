//
// Kosaraju's algorithm to find strongly connected components in C++
//

#include <algorithm>
#include <boost/fusion/adapted.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/spirit/home/x3.hpp>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>

using namespace std;  // NOLINT I don't care about this right now

class Edge;

class Vertex {
 public:
  Vertex() = default;
  explicit Vertex(uint32_t node_id_in) : node_id_{node_id_in} {}
  void add_edge(Vertex& tail_vertex);
  bool operator==(Vertex const& other) {
    return this->node_id() == other.node_id();
  }

  size_t num_edges() const { return edges().size(); }

  std::list<Edge>& edges(bool is_reverse = false) {
    return is_reverse ? reverse_edges_ : edges_;
  }
  std::list<Edge> const& edges(bool is_reverse = false) const {
    return is_reverse ? reverse_edges_ : edges_;
  }

  uint32_t node_id() const { return node_id_; }

  uint32_t was_visited() const { return was_visited_; }
  void set_was_visited(bool was_visited_in) { was_visited_ = was_visited_in; }

  uint32_t finishing_time() const { return finishing_time_; }
  void set_finishing_time(uint32_t finishing_time_in) {
    finishing_time_ = finishing_time_in;
  }

 private:
  std::list<Edge>
      edges_{};  // only edges of which the current Vertex is the head
  std::list<Edge> reverse_edges_{};
  uint32_t node_id_{0};
  uint32_t finishing_time_{0};
  bool was_visited_{false};
};

void Vertex::add_edge(Vertex& tail_vertex) {
  edges_.emplace_back(*this, tail_vertex);
  tail_vertex.reverse_edges_.emplace_back(tail_vertex, *this);
}

template <>
struct std::hash<Vertex> {
  std::size_t operator()(Vertex const& node) const noexcept {
    return std::hash<uint32_t>{}(node.node_id());
  }
};

class Edge {
 public:
  Edge(Vertex& head_node, Vertex& tail_node)
      : head_node_{&head_node}, tail_node_{&tail_node} {}

  bool operator==(Edge const& other) {
    return head_node_->node_id() == other.head_node_->node_id() &&
           tail_node_->node_id() == other.tail_node_->node_id();
  }

  Vertex& head_node() { return *head_node_; }
  Vertex const& head_node() const { return *head_node_; }
  Vertex& tail_node() { return *tail_node_; }
  Vertex const& tail_node() const { return *tail_node_; }

 private:
  Vertex* head_node_;
  Vertex* tail_node_;
};

struct Scc {
  std::list<Vertex*> nodes;
};

void dfs_scc_first(bool is_reverse, Vertex& node,
                   std::stack<Vertex*>& vertices_first_past_order) {
  node.set_was_visited(true);
  for (auto& edge : node.edges(is_reverse)) {
    Vertex& tail_node = edge.tail_node();
    if (!tail_node.was_visited()) {
      dfs_scc_first(is_reverse, tail_node, vertices_first_past_order);
    }
  }
  vertices_first_past_order.push(&node);
}

void dfs_scc_second(bool is_reverse, Vertex& node, Scc& scc) {
  node.set_was_visited(true);
  scc.nodes.push_back(&node);
  for (auto& edge : node.edges(is_reverse)) {
    Vertex& tail_node = edge.tail_node();
    if (!tail_node.was_visited()) {
      dfs_scc_second(is_reverse, tail_node, scc);
    }
  }
}

struct Edge_Node_Ids {
  uint32_t head_node{0};
  uint32_t tail_node{0};
};

BOOST_FUSION_ADAPT_STRUCT(Edge_Node_Ids, head_node, tail_node)

class Graph {
 public:
  Graph() = default;
  explicit Graph(std::size_t num_vertices) : vertices_(num_vertices) {}

  void do_scc();
  void reset_visited_nodes();

  Vertex& add_vertex(uint32_t node_id);
  void add_edge(uint32_t node_id_0, uint32_t node_id_1);
  void add_edge(Edge_Node_Ids node_ids);

  size_t num_vertices() const { return vertices_.size(); }
  size_t num_edges() const;

  bool is_reverse() { return is_reverse_; }
  void set_reverse() { is_reverse_ = true; }
  void set_forward() { is_reverse_ = false; }

  std::stack<Vertex*>& vertices_first_past_order() {
    return vertices_first_past_order_;
  }
  std::stack<Vertex*> const& vertices_first_past_order() const {
    return vertices_first_past_order_;
  }

  std::vector<Scc> const& scces() const { return scces_; }

 private:
  std::unordered_map<uint32_t, Vertex> vertices_;
  std::vector<Scc> scces_{};
  std::stack<Vertex*> vertices_first_past_order_{};
  bool is_reverse_{false};
};

size_t Graph::num_edges() const {
  size_t num_edges{0};
  for (auto const& node : vertices_) {
    num_edges += node.second.num_edges();
  }
  return num_edges;
}

void Graph::reset_visited_nodes() {
  for (auto& pair : vertices_) {
    Vertex& node = pair.second;
    node.set_was_visited(false);
  }
}

Vertex& Graph::add_vertex(uint32_t node_id) {
  auto node2 = vertices_.emplace(std::piecewise_construct,
                                 std::forward_as_tuple(std::move(node_id)),
                                 std::forward_as_tuple(node_id));
  return node2.first->second;
}

void Graph::add_edge(uint32_t node_id_0, uint32_t node_id_1) {
  auto& node0 = add_vertex(node_id_0);
  auto& node1 = add_vertex(node_id_1);
  node0.add_edge(node1);
}

void Graph::add_edge(Edge_Node_Ids node_ids) {
  auto& node0 = add_vertex(node_ids.head_node);
  auto& node1 = add_vertex(node_ids.tail_node);
  node0.add_edge(node1);
}

void Graph::do_scc() {
  reset_visited_nodes();
  for (auto& pair : vertices_) {
    Vertex& node = pair.second;
    if (!node.was_visited()) {
      dfs_scc_first(false, node, vertices_first_past_order_);
    }
  }

  // reverse the graph & reset nodes
  set_reverse();
  reset_visited_nodes();

  // process all nodes according to stack
  while (!vertices_first_past_order_.empty()) {
    auto& node = *vertices_first_past_order_.top();
    vertices_first_past_order_.pop();
    if (!node.was_visited()) {
      auto& scc = scces_.emplace_back();
      dfs_scc_second(true, node, scc);
    }
  }

  auto comp = [&](Scc const& scc0, Scc const& scc1) {
    return scc0.nodes.size() > scc1.nodes.size();
  };
  std::sort(scces_.begin(), scces_.end(), comp);

  // reset the reverse graph
  set_forward();
}

int main() {
  // TEST 0 - add a simple directed graph
  static constexpr std::size_t NUM_NODES_GRAPH_0{5};
  auto graph = std::unique_ptr<Graph>(new Graph());

  graph->add_edge(1, 0);
  graph->add_edge(0, 2);
  graph->add_edge(2, 1);
  graph->add_edge(0, 3);
  graph->add_edge(3, 4);

  graph->do_scc();

  size_t const max_index{
      std::min(static_cast<size_t>(5), graph->scces().size())};
  cout << "top SCC sizes:" << endl;
  for (uint32_t index = 0; index < max_index; ++index) {
    cout << graph->scces().at(index).nodes.size() << endl;
  }

  // Coursera Quiz for SCC graph
  cout << endl << endl;
  cout << "Corsera Quiz Top SCCs:" << endl;

  // Build a graph from a text file
  namespace x3 = boost::spirit::x3;
  static constexpr uint32_t max_nodes{875714};
  Graph graph1(max_nodes);

  std::string fname("data/SCC.txt");
  boost::iostreams::mapped_file source{fname,
                                       boost::iostreams::mapped_file::readonly};
  using iterator = char const*;
  boost::iterator_range<iterator> range{
      source.const_data(), source.const_data() + source.size()};  // NOLINT

  iterator f = range.begin();
  iterator l = range.end();

  Edge_Node_Ids data;
  while (f && f != l) {
    if (phrase_parse(f, l, x3::uint_ >> x3::uint_, x3::space, data)) {
      if (data.head_node != data.tail_node) {
        graph1.add_edge(data);
      }
    }
  }

  // Do the SCC from the graph built from a text file
  graph1.do_scc();

  // Print the top 5 largest SCCs
  size_t const max_index2{
      std::min(static_cast<size_t>(5), graph1.scces().size())};
  cout << "top SCC sizes:" << endl;
  for (uint32_t index = 0; index < max_index2; ++index) {
    cout << graph1.scces().at(index).nodes.size() << endl;
  }

  return 0;
}